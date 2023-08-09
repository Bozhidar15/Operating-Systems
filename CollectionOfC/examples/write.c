#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
int main(void){
	int fd = open("p2", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	for (uint8_t i=100; i<154; i++){
		write(fd, &i, sizeof(i));
	}
	for (uint8_t i=174; i<184; i++){
		write(fd, &i, sizeof(i));
	}
}
