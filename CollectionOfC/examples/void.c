#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <err.h>
#include <stdio.h>
typedef struct {
uint8_t y;
uint16_t x;
uint32_t h;
}__attribute__((packed)) coord;

void write_(int fd, void *data,int len){
	if(write(fd,data,len)==-1){
		err(1,"write\n");
	}
}

void read_(int fd, void *data,int len){
	if(read(fd,data,len)==-1){
		err(1,"read\n");
	}
}
int main(int argc,char** argv){
	coord c;
	c.y=8;
	c.x=18;
	c.h=38;
	uint16_t p=99;
	int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0666);
	if(fd==-1){err(1,"open\n");}
	dprintf(1,"%d %d %d %d\n",c.y,c.x,c.h,p);
	write_(fd,&c,7);
	write_(fd,&p,1);
	if(lseek(fd,0,SEEK_SET)==-1){err(1,"seek\n");}
	coord c1;
	uint16_t p1;
	read_(fd,&c1,sizeof(c1));
	read_(fd,&p1,sizeof(p1));
	dprintf(1,"%d %d %d %d\n",c1.y,c1.x,c1.h,p1);

}
