#include <stdint.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
typedef struct {
	uint16_t offset;
	uint8_t org;
	uint8_t new;
}elements;

void checkStructFile(int fd){
	struct stat s;
	fstat(fd, &s);
	if(s.st_size % 4 != 0){
		errx(1, "Patch file size must be divisible by 4\n");
	}
}

void readStruct(int fd, int fd2){
	elements el;
	int bytes;
	while((bytes=read(fd, &el, sizeof(el)))){
		uint8_t curr;
		if (lseek(fd2, el.offset, SEEK_SET)==-1){
			err(1, "couldn't lseek\n");
		}
		if((bytes=read(fd2, &curr, sizeof(curr)))==-1){
			err(1, "couldn't read exact symbol after lseek\n");
		}
		if (curr != el.org){
			errx(1,"symbol not matching\n");
		}
		if (lseek(fd2, el.offset, SEEK_SET)==-1){
			err(1, "couldn't lseek\n");
		}
		if ((bytes=write(fd2,&el.new,sizeof(el.new))==-1)){
			err(1,"couldn't change symbol\n");
		}
	}
	if (bytes==-1){
		err(1,"couldn't read struct from file\n");
	}
}

void copy(int fd1, int fd2){
	uint8_t el;
	int bytes;
	while ((bytes=read(fd1, &el, sizeof(el)))){
		if ((bytes=write(fd2, &el, sizeof(el)))==-1){
			err(1,"couldn't write on second file\n");
		}
	}
	if (bytes<0){
		err(1,"couldn't read from 1st file\n");
	}
}

int main(int argc, char **argv){
	if (argc != 4){
		errx(1,"unvalid number of arguments!\n");
	}
	int fd_p, fd_1, fd_2;
	if ((fd_p=open(argv[1], O_RDONLY))==-1){
		err(1, "couldn't open patch\n");
	}
	checkStructFile(fd_p);
	if ((fd_1=open(argv[2], O_RDONLY))==-1){
		err(1, "couldn't open first\n");
	}
	if ((fd_2=open(argv[3], O_RDWR | O_TRUNC | O_CREAT, 0666))==-1){
		err(1, "couldn't open file to write\n");
	}
	copy(fd_1,fd_2);
	readStruct(fd_p,fd_2);
	close(fd_p);
	close(fd_1);
	close(fd_2);
}	
