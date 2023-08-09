#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>

int fd;
char *filename;

void lseekSafe(int offset) {
	if (lseek(fd, offset, SEEK_SET) == -1) {
		err(25, "Error lseek in file %s", filename);
	}
}

uint32_t readNumber(int position) {
	lseekSafe(position * 4);

	uint32_t num;
	if (read(fd, &num, 4) != 4) {
		err(26, "Error reading number from file %s", filename);
	}

	return num;
}

void writeSafe(uint32_t num) {
	if (write(fd, &num, 4) == -1) {
		err(27,"Error writing to file %s", filename);
	}
}

int main (int argc ,char **argv) {
	if (argc != 2) {
		errx(1, "Error: Expected 1 argument");
	}

	if ((fd = open(argv[1], O_RDWR)) == -1) {
		err(2, "Error opening file %s", argv[1]);
	}

	filename = argv[1];

	struct stat s;
	if (fstat(fd, &s) == -1) {
		err(3, "Error fstat");
	}

	if (s.st_size % 4 != 0) {
		errx(4, "Error: Incorrect file size");
	}

	int count = s.st_size / 4;
	if (count > 100000000) {
		errx(5, "Error: Too many numbers");
	}

	//selection sort
	
	for(int i = 0; i < count - 1; i++) {
		int minIndex = i;
		uint32_t minNumber = readNumber(i);

		for (int j = i + 1; j < count; j++) {
			uint32_t cur = readNumber(j);

			if (cur < minNumber) {
				minIndex = j;
				minNumber = cur;
			}
		}

		if (minIndex != i) {
			uint32_t toMove = readNumber(i);

			lseekSafe(minIndex * 4);
			writeSafe(toMove);

			lseekSafe(i * 4);
			writeSafe(minNumber);
		}
	}

	close(fd);
	exit(0);
}		
