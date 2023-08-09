#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
int main(int argc, char ** argv){
	int fd =open(argv[1], O_WRONLY);
	uint8_t h=88;
	lseek(fd, 2, SEEK_SET);
	write(fd, &h, 1);

}
