// Реализирайте команда wc, с един аргумент подаден като входен параметър
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <err.h>

int main (int argc, char* argv[]){
	int fd1;
	int lines = 0;
	int words = 0;
	int chars = 0;

	if (argc != 2) {
		errx(1, "expected 1 argument");
	}

	if ( (fd1 = open(argv[1], O_RDONLY)) == -1 ) {
		err(1, "could not open file %s for reading", argv[1]);
	}

	int bytes_read;
	char buf[4096];
	while ( (bytes_read = read(fd1, buf, sizeof(buf))) > 0 ) {
		for (int i = 0; i < bytes_read; i++) {
			char c = buf[i];
			if (c=='\n') {
				lines++;
				words++;
			}

			if (c==' ') {
				words++;
			}

			chars++;
		}
	}
	if (bytes_read < 0) {
		err(1, "could not read data");
	}

	dprintf(1, "File %s has:\n%d number of lines.\n%d number of words.\n%d number of chars.\n",
		argv[1], lines, words, chars
	);

	close(fd1);
}
