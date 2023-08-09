#include <string.h>
#include <err.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc,char**argv){
	while(true){
		if(write(1,"s0600004:",strlen("s0600004:"))!=strlen("s0600004:")){
			err(1,"err write");
		}
		char arr[1024];
		int bytes;
		if((bytes=read(0,arr,sizeof(arr)))==-1){
			err(2,"error while reading");
		}
		arr[bytes-1]='\0';
		dprintf(1,"read:%s!\n",arr);
		if(strcmp(arr,"exit")==0){
			break;
		}
		pid_t a = fork();
		if(a==-1){
			err(5,"couldn,t fork");
		}
		if(a==0){
			char final[1024];
			strcpy(final,"/bin/");
			strcat(final,arr);
			dprintf(1,"%s!\n",final);
			if(execl(final,arr,(char*)NULL)==-1){
				err(3,"error exec command");
			}
		}
		int status;
        if (wait(&status) == -1) {
            err(4, "Could not wait for child process to finish");
        }

        if (!WIFEXITED(status)) {
            errx(5, "Child process did not terminate normally");
        }

        //if (WEXITSTATUS(status) != 0) {
          //  errx(6, "Child process finished with exit code not 0");
       // }
	}
}
