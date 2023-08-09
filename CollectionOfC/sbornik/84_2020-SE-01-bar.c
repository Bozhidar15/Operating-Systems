#include <err.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
int main (int argc, char**argv){
	if(argc!=2){
		errx(1,"invalid number of arguments");
	}
	int fd;
	if((fd=open("temp.pipe",O_RDONLY))==-1){
		err(2,"couldn't open pipe");
	}
	if(dup2(fd,0)==-1){
		err(3,"couldn't dup2");
	}
	pid_t a = fork();
	if(a==0 && execl(argv[1],argv[1],(char*)NULL)==-1){
		err(4,"couldn't execl");
	}
	if(wait((int *)NULL)==-1){
		err(6,"couldn't wait");
	}
	close(fd);
	unlink("temp.pipe");
}
