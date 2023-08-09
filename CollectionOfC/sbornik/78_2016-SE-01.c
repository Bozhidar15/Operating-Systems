#include <err.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char **argv){
	if(argc!=2){
		errx(1,"invalid number of arg");
	}

	int p[2];
	if (pipe(p)==-1){
		err(2,"couldn,t pipe");
	}
	int fd;
	pid_t a = fork();
	if(a==0){
		close(p[0]);
		if(dup2(p[1],1)==-1){
			err(4,"coouldn,t dup");
		}
		if (execlp("cat","cat",argv[1],(char*)NULL)==-1){
			close(p[1]);
			err(3,"couldn,t exec");
		}
	}
	else{
		wait(NULL);
		close(p[1]);
		if(dup2(p[0],0)==-1){
			err(4,"coouldn,t dup");
		}
		if(execlp("sort","sort",(char*)NULL)){
			close(p[0]);
			err(3,"couldn,t exec");
		}
	}
}
