// Напишете програма, която приема 2 аргумента: команда без параметри
// и име на файл. Програмата да изпълнява командата, пренасочвайки
// нейния изход във файла
#include <err.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char* argv[]) {
	if (argc != 3) {
		warnx("usage: %s <command> <filename>", argv[0]);
		errx(1, "%s executes the given command, redirecting its output to the given file", argv[0]);
	}
	int fd = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT, 0666);
	if(fd ==-1){
		err(3,"error open");
	}
	close(1);
	dup(fd);
	if (execlp(argv[1],argv[1],(char*)NULL)==-1){
		err(3,"error exec");
	}
	
}
