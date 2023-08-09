// Напишете програма, която сортира бинарен файл, съдържащ
// поредица от uint16_t числа.

// Сортирането направете, извиквайки външната команда sort(1)

// Нека програмата приема 2 аргумента: файл от който четем,
// и файл в който пишем

#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <linux/close_range.h>

void safe_dup2(int oldfd, int newfd) {
	if (oldfd == newfd) {
		return;
	}

	if (dup2(oldfd, newfd) < 0) {
		err(1, "could not dup");
	}
	close(oldfd);
}

void close_all_fds_after(int fd_num) {
	int result = close_range(fd_num, ~0U, 0);
	if (result < 0) {
		err(1, "could not close range");
	}
}

void spawn_reader(char* filename, int out_fd) {
	pid_t pid = fork();
	if (pid < 0) {
		err(1, "could not fork");
	}
	if (pid > 0) {
		return;
	}

	safe_dup2(out_fd, 1);
	out_fd = 1;
	close_all_fds_after(3);

	int in_fd = open(filename, O_RDONLY);
	if (in_fd < 0) {
		err(1, "could not open %s", filename);
	}

	while (true) {
		uint16_t num;
		int bytes_read = read(in_fd, &num, sizeof(num));
		if (bytes_read == 0) {
			break;
		}
		if (bytes_read < 0) {
			err(1, "could not read from %s", filename);
		}
		if (bytes_read != sizeof(num)) {
			errx(1, "could not read whole number at once");
		}

		char num_text[10];
		snprintf(num_text, sizeof(num_text), "%d\n", num);
		int bytes_written = write(out_fd, num_text, strlen(num_text));
		if (bytes_written < 0) {
			err(1, "could not write");
		}
		if (bytes_written != (int)strlen(num_text)) {
			errx(1, "could not write number text at once");
		}
	}
	exit(0);
}

uint16_t parse_number(char* buf) {
	return (uint16_t)atoi(buf);
}

bool read_num_as_text(int fd, uint16_t* result) {
	char buf[10];
	for (size_t i = 0; i < sizeof(buf) - 1; i++) {
		int bytes_read = read(fd, &buf[i], 1);
		if (bytes_read == 0) {
			if (i == 0) {
				return false;
			} else {
				errx(1, "file ended in middle of number");
			}
		}
		if (bytes_read < 0) {
			err(1, "could not read number");
		}
		if (buf[i] == '\n') {
			buf[i] = '\0';
			*result = parse_number(buf);
			return true;
		}
	}

	errx(1, "line too long");
}

void spawn_writer(int in_fd, char* filename) {
	pid_t pid = fork();
	if (pid < 0) {
		err(1, "could not fork");
	}
	if (pid > 0) {
		return;
	}
	
	safe_dup2(in_fd, 0);
	in_fd = 0;
	close_all_fds_after(3);

	int out_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (out_fd < 0) {
		err(1, "could not open %s", filename);
	}

	uint16_t num;
	while (read_num_as_text(in_fd, &num)) {
		int bytes_written = write(out_fd, &num, sizeof(num));
		if (bytes_written < 0) {
			err(1, "could not write data");
		}
		if (bytes_written != sizeof(num)) {
			errx(1, "could not write whole number at once");
		}
	}

	close(out_fd);

	exit(0);
}

void spawn_sorter(int in_fd, int out_fd) {
	pid_t pid = fork();
	if (pid < 0) {
		err(1, "could not fork");
	}
	if (pid > 0) {
		return;
	}

	safe_dup2(in_fd, 0);
	safe_dup2(out_fd, 1);

	close_all_fds_after(3);

	execlp("sort", "sort", "-n", (char*)NULL);
	err(1, "could not exec sort");
}
void wait_for_child(void) {
	int status;
	int wait_status = wait(&status);
	if (wait_status < 0) {
		warn("could not wait");
		return;
	}
	if (!WIFEXITED(status)) {
		warnx("child was killed");
		return;
	}
	if (WEXITSTATUS(status) != 0) {
		warnx("child failed");
		return;
	}
}

void make_pipe(int p[2]) {
	if (pipe(p) < 0) {
		err(1, "could not create pipe");
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		warnx("usage: %s <input file> <output file>", argv[0]);
		errx(1, "%s sorts a file of unsigned 16-bit integers", argv[0]);
	}

	int p1[2];
	make_pipe(p1);

	int p2[2];
	make_pipe(p2);

	spawn_reader(argv[1], p1[1]);
	spawn_sorter(p1[0], p2[1]);
	spawn_writer(p2[0], argv[2]);

	close_all_fds_after(3);

	wait_for_child();
	wait_for_child();
	wait_for_child();

	return 0;
}
