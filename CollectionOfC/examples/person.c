#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdint.h>

typedef struct {
	char name[15];
	uint8_t age;
	uint16_t num_cactuses;
} person_t;

void checked_write(int fd, void* buf, ssize_t n) {
	int bytes_written = write(fd, buf, n);
	if (bytes_written < 0) {
		err(1, "could not write");
	}
	if (bytes_written != n) {
		errx(1, "did not write all data at once, giving up");
	}
}

void checked_read(int fd, void* buf, ssize_t n) {
	int bytes_written = read(fd, buf, n);
	if (bytes_written < 0) {
		err(1, "could not read");
	}
	if (bytes_written != n) {
		errx(1, "did not read all data at once, giving up");
	}
}

void write_person(const char* filename, person_t* p) {
	int fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd < 0) {
		err(1, "could not open %s", filename);
	}

	checked_write(fd, p->name, sizeof(p->name));
	checked_write(fd, &p->age, sizeof(p->age));
	checked_write(fd, &p->num_cactuses, sizeof(p->num_cactuses));

	close(fd);
}

void read_person(const char* filename, person_t* p) {
	int fd = open(filename, O_RDONLY);
	if (fd < 0) {
		err(1, "could not open %s for reading", filename);
	}

	checked_read(fd, p->name, sizeof(p->name));
	checked_read(fd, &p->age, sizeof(p->age));
	checked_read(fd, &p->num_cactuses, sizeof(p->num_cactuses));

	close(fd);
}

void print_person(person_t* p) {
	dprintf(1, "name: %s, age: %d, cactuses: %d\n",
			p->name, p->age, p->num_cactuses);
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		errx(1, "usage: %s <read|write> <filename>", argv[0]);
	}

	if (strncmp(argv[1], "write", strlen("write")) == 0) {
		person_t ivan;
		ivan.age = 32;
		ivan.num_cactuses = 5000;
		strncpy(ivan.name, "Ivan", sizeof(ivan.name));

		write_person(argv[2], &ivan);
	} else if (strncmp(argv[1], "read", strlen("read")) == 0) {
		person_t ivan;
		read_person(argv[2], &ivan);
		print_person(&ivan);
	} else {
		errx(1, "unknown action: %s", argv[1]);
	}
}
