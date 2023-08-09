#include <err.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

void safe_write(int fd, const void* buf, size_t n) {
	int bytes_written = write(fd, buf, 1);
	if (bytes_written < 0) {
		err(1, "could not write");
	}
	if (bytes_written != (int)n) {
		errx(1, "could not write %lu bytes at once", n);
	}
}

void encode_byte(int fd, uint8_t c) {
	if (c == 0x00 || c == 0x55 || c == 0xff || c == 0x7d) {
		c = c ^ 0x20;
		safe_write(fd, "\x7d", 1);
		safe_write(fd, &c, 1);
	} else {
		safe_write(fd, &c, 1);
	}
}

int main(void) {
	uint8_t c;
	int bytes_read;
	int fd;
	while ((bytes_read = read(0, &c, 1)) == 1) {
		encode_byte(1, c);
		if (rand() % 10 == 0) {
			safe_write(1, "\x55", 1);
		}
	}
	if (bytes_read != 0) {
		err(1, "could not read from stdin");
	}
}
