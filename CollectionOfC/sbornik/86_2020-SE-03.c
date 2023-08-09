#include <err.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

typedef struct {
	char name[8];
	uint32_t offset;
	uint32_t len;
}data;

uint16_t calc(data *d){
	int fd = open(d->name,O_RDONLY);
	if (fd<0){
		err(3,"error opening file");
	}
	int position=lseek(fd, d->offset*2, SEEK_SET);
	if (position < 0){
		err(4,"error lseek");
	}
	uint16_t number=0,curr=0;

	for (uint16_t i=0; i<d->len; i++){
		if(read(fd, &curr,sizeof(curr)) < 0){
			err(1, "couldn't read");
		}
		if(i==0) {
			number=curr;
			continue;
		}
		number = number ^ curr;
	}
	return number;
}

void calculateAll(int fd){
	uint16_t all=0x0000, curr=0;
	int bytes;
	while ((bytes = read(fd, &curr,sizeof(curr)))){
		all=all^curr;
	}
	if (bytes < 0){
		err(6,"error reading from file");
	}
	dprintf(0, "final result:%d", all);
	close(fd);
}

void readStruct(int fd){
	int p[2];
	if (pipe(p)<0){
		err(5,"error making pipe");
	}	
	data d;
	int bytes=0;
	int counter=0;
	while ((bytes = read(fd, &d,sizeof(data)))){
		counter++;
		pid_t a = fork();
		if (a==-1){
			err(1,"couldn't fork");
		}
		if (a==0){
			close(p[0]);
			uint16_t curr= calc(&d);
			if (write(p[1],&curr, sizeof(curr))==-1){
				err(1,"error writing into pipe");
			}
			close(p[1]);
			exit(0);
		}
	}
	if (bytes < 0){
		err(6,"error reading from file");
	}
	for (int i=0; i<counter; i++){
		wait(NULL);
	}
	close(p[1]);
	calculateAll(p[0]);
}

int main(int argc, char ** argv){
	if (argc != 2 ){
		err(2, "invalid number of arg");
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0){
		err(3,"error opening file");
	}
	struct stat s;
	fstat(fd, &s);
	if (s.st_size %8 != 0 ){
		errx(7,"file not fstat");
	}
	readStruct(fd);
}


