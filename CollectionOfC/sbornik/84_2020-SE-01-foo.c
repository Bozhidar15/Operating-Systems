#include <err.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv){
	if(argc!=2){
		errx(1,"invalid arg");
	}
	const char* mk="temp.pipe";
	mkfifo(mk,0666);
	int fd;
	if((fd=open(mk,O_WRONLY))==-1){
		err(2,"couldn't opne");
	}
	if(dup2(fd,1)==-1){
		err(4,"couldn't dup2");
	}
	if(execlp("cat","cat",argv[1],(char*)NULL)==-1){
		err(3,"couldn't exec");
	}
	close(fd);
}
