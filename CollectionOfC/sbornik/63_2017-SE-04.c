#include <unistd.h>
#include <err.h>
#include <fcntl.h>
#include <string.h>

void fdRead(int fd){
	char arr[4096];
	int bytes;
	while((bytes=read(fd, arr, sizeof(arr)))){
		if (write(1, arr, bytes)==-1){
			err(1, "couldn't write to stdout\n");
		}
	}
	if (bytes==-1){
		err(1, "couldn't read from this fd%d\n",fd);
	}
}
void arguments(int num, char ** argv){
	int fd;
	for(int i = 1; i<num; i++){
		if(strcmp(argv[i],"-")==0){
			fdRead(0);	
		}else {
			if((fd=open(argv[i],O_RDONLY))==-1){
				err(1,"couldn't open current file\n");
			}
			fdRead(fd);
			close(fd);
		}
	}
}
int main(int argc, char **argv){
	if (argc == 1){
		fdRead(0);
	}else {
		arguments(argc, argv);
	}
}
