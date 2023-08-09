/*
	Реализирайте команда swap, разменяща съдържанието на два файла, подадени като
	входни параметри. Приемаме, че двата файла имат еднакъв брой символи. Може да
	модифицирате решението, да работи и когато нямат еднакъв брой символи.
*/

#include <stdio.h>
#include <err.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void lseek_safe(int fd, off_t offset, int whence) {
	if (lseek(fd, offset, whence) < 0) {
		err(1, "could not seek");
	}
}

void ftruncate_safe(int fd, size_t size) {
	if (ftruncate(fd, size) < 0) {
		err(1, "could not truncate");
	}
}

void copy_data(int fd_from, int fd_to) {
	char buf[4096];
	ssize_t read_size;

	while ((read_size = read(fd_from, buf, sizeof(buf))) > 0) {
		int write_result = write(fd_to, buf, read_size);

		if (write_result < 0) {
			err(1, "error while writing");
		}
		if (write_result != read_size ) {
			errx(1, "could not write all data at once");
		}
	}

	if (read_size != 0) {
		err(2, "Error while reading");
	}
}

int main (int argc, char* argv[])
{
	if (argc != 3) {
		errx(1, "err");
	}

	int fd1;
	fd1 = open(argv[1], O_RDWR);
	if (fd1 == -1) {
		err(2, "%s", argv[1]);
	}

	int fd2;
	fd2 = open(argv[2], O_RDWR);
	if (fd2 == -1) {
		err(3, "%s", argv[2]);
	}

	int fd3;
	fd3 = open("my_temp_file", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd3 == -1) {
		err(4, "%s", "my_temp_file");
	}

	copy_data(fd1, fd3);

	lseek_safe(fd1, 0, SEEK_SET);
	ftruncate_safe(fd1, 0);

	copy_data(fd2, fd1);

	lseek_safe(fd2, 0, SEEK_SET);
	ftruncate_safe(fd2, 0);
	lseek_safe(fd3, 0, SEEK_SET);

	copy_data(fd3, fd2);

	close(fd1);
	close(fd2);
	close(fd3);

	exit(0);
}

