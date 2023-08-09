// Напишете програма, която извиква произволен
// брой подадени команди без параметри паралелно
// с тръби между тях

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

void spawn_command(char* command, int in_fd, int out_fd) {
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

	execlp(command, command, (char*)NULL);
	err(1, "could not exec %s", command);
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
	const int max_commands = 100;

	int num_commands = argc - 1;


	int pipes[max_commands][2];

	for (int i = 1; i < num_commands; i++) {
		make_pipe(pipes[i]);
	}
	pipes[0][0] = 0;
	pipes[num_commands][1] = 1;

	for (int i = 0; i < num_commands; i++) {
		spawn_command(argv[i+1], pipes[i][0], pipes[i+1][1]);
	}

	close_all_fds_after(3);

	for (int i = 0; i < num_commands; i++) {
		wait_for_child();
	}

	return 0;
}
