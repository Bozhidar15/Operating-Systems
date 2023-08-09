// Напишете програма, която приема 2 аргумента: команда без параметри
// и име на файл. Програмата да изпълнява командата, пренасочвайки
// нейния изход във файла
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char* argv[]) {
	if (argc != 2) {
		warnx("usage: %s <path>", argv[0]);
		errx(1, "%s find regular files", argv[0]);
	}	
	int p[2];
	if (pipe(p)==-1){
		err(4, "pipe");
	}
	pid_t a = fork();
	if(a==0){
		close(p[0]);
		dup2(p[1], 1);
		if(execlp("find","find",argv[1],"-type", "f",(char*)NULL)==-1){
			err(4, "error exec");
		}
	}else{
		close(p[1]);
		dup2(p[0],0);
		if (execlp("wc","wc","-l",(char *)NULL)==-1){
			err(4,"error exec");
		}
	}

}
