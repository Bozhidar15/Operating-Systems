#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main(int argc,char **argv){
	if(argc!=3){
		errx(1,"invalid number of arguments\n");
	}
	const int len=atoi(argv[1]);
	const int time=atoi(argv[2]);
	const char* per="DING\n";
	const char* child="DONG\n";
	for(int i=0;i<len;i++){
		if(write(1,per,strlen(per))!=strlen(per)){
			err(3,"Parent couldn't write to stdout properly\n");
		}
		pid_t a=fork();
		if(a==-1){
			err(2,"couldn't fork properly\n");
		}
		if(a==0){
			if(write(1,child,strlen(child))!=strlen(child)){
				err(3,"Child couldn't write to stdout properly\n");
			}
			exit(0);
		}
		int status;
		if(wait(&status)==-1){
			err(4,"Error occured while using wait()\n");
		}
		if(!WIFEXITED(status)){
			errx(5,"Child process didn't terminate normally\n");
		}
		else if(WEXITSTATUS(status)){
			errx(6,"Child process exited with exit status != 0\n"); 
		}
		sleep(time);
	}

}
