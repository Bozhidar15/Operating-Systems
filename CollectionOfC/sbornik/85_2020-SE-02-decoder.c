#include <err.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
int main(int argc, char ** argv ){
	if (argc!=3){
		errx(1,"invalid number of parameters");
	}
	int fd_from, fd_to;
	int bytes=0;
	if((fd_from=open(argv[1],O_RDONLY))==-1){
		err(2,"couldn't open first file");
	}
	if((fd_to=open(argv[2],O_WRONLY | O_TRUNC | O_CREAT, 0666))==-1){
		err(2,"couldn't open first file");
	}
	int p[2];
	if(pipe(p)==-1){
		err(4,"couldn't pipe");
	}
	pid_t a = fork();
	if(a==-1){
		err(3,"couldn't fork");
	}
	if(a==0){
		close(p[0]);
		if(dup2(p[1],1)==-1){
			err(5,"couldn't dup2");
		}
		if(execlp("cat","cat",argv[1],(char*)NULL)==-1){
			err(6,"couldn't exec");
		}
	}
	int status;
	if(wait(&status)==-1){
		err(4,"couldn't wait");
	}
	close(p[1]);
	if(dup2(p[0],0)==-1){
		err(5,"couldn't dup2");
	}
	char c;
	//dprintf(1,"tuk");
	while((bytes=read(0, &c, sizeof(c))) == sizeof(c)){
		//dprintf(1,"%s\n",c);
		if(c==0x55){
			continue;
		}else if(c==0x7D){
			if((bytes=read(0,&c,1))!=1){
				err(8,"couldn't read agein");
			}
			
			char b=c^0x20;
			if(!(b ==0x00 || b == 0xFF || b == 0x55 || b == 0x7D)){
				err(9,"invalid symbol");
			}
			if(write(1,&c,1)!=1){
				err(10,"invalid write");
			}
			continue;
		}
		if(write(1,&c,1)!=1){
			err(10,"invalid write");
		}
		
	}
	if(bytes==-1){
		err(4,"error while reading");
	}
	close(p[0]);
	close(fd_from);
	close(fd_to);
}
