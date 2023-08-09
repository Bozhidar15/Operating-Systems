#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
int main(void){
	int fd = open("p1", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	uint8_t p='o';
	uint16_t pp=1;
	write(fd,&pp, sizeof(pp));	
	write(fd,&p, sizeof(p));
	p='Y';
	write(fd,&p, sizeof(p));	
	pp=5;
	write(fd,&pp, sizeof(pp));
	p='d';
	write(fd,&p, sizeof(p));
	p='Y';
	write(fd,&p, sizeof(p));
	//write(fd,"bozhidar abadzhiev", strlen("bozhidar abadzhiev"));
	//for (uint8_t i=100; i<154; i++){
	//	write(fd, &i, sizeof(i));
	//}
	//for (uint8_t i=174; i<184; i++){
	//	write(fd, &i, sizeof(i));
	//}
}
