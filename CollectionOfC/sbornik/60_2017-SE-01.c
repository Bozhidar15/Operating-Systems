#include <fcntl.h>
#include <err.h>
#include <unistd.h>
#include <stdint.h>

typedef struct {
	uint16_t offset;
	uint8_t orig;
	uint8_t new;
}data;

void validation(int *fd, const char * file){
	*fd = open(file, O_RDONLY);
	if (*fd == -1){
		err(2, "error opening");
	}
}

int main(int argc, char ** argv){
	if (argc != 4){
		errx(1, "invalid number of elements");
	}
	int fd_o=0, fd_m=0;
	validation(&fd_o, argv[1]);
	validation(&fd_m, argv[2]);

	int fd_w = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_w == -1){
		err(2, "error opening");
	}
	data curr;
	uint8_t temp_o, temp_m;
	uint16_t counter=0;
	int bytes=0;
	while ((bytes=read(fd_o, &temp_o, sizeof(temp_o)))){
		
		if ((bytes=read(fd_m, &temp_m,sizeof(temp_m)))<0){
			err(2, "error reading from modif file");
		}else if(bytes==0){
			errx(2,"error mod file find end of file while org file not");
		}
		
		if(temp_o != temp_m){
			curr.offset=counter;
			curr.orig=temp_o;
			curr.new=temp_m;
			if (write(fd_w,&curr, sizeof(curr))<0){
				err(3,"error writing struct to file");
			}
		}
		counter++;
	}
	if (bytes<0){
		err(2,"error reading from orig file");
	}
	if (read(fd_m, &temp_m,sizeof(temp_m))!=0){
			err(3, "orig file end but modif file is not");
	}
}
