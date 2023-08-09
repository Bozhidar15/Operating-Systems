// Напишете програма, която сортира бинарен файл, съдържащ
// поредица от uint16_t числа.

// Сортирането направете, извиквайки външната команда sort(1)

// Нека програмата приема 2 аргумента: файл от който четем,
// и файл в който пишем

int main(int argc, char* argv[]) {
	if (argc != 3) {
		warnx("usage: %s <input file> <output file>",argv[0]);
		errx(1, "%s sorts a file of unsigned 16-bit integers",argv[0]);
	}
	uint16_t a=0;
	int bytes =0;
	int fd_in=read(argv[1],O_RDONLY);
	if (fd_in <0){
		err(2,"read err")
	}
	int fd_out=read(argv[2],O_WRONLY|O_TRUNC|O_CREAT,0666);
	if (fd_out <0){
		err(2,"read err")
	}
	int p[2];
	if (pipe(p)==-1){
		err(5,"pipe");
	}
	close(p[0]);
	dup2(p[1],1);
	while (bytes=read(fd_in,&a,sizeof(a))){
		dprintf("%d\n",a);
	}
	

	return 0;
}
