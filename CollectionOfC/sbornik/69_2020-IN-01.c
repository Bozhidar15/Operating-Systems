#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <err.h>
#include <fcntl.h>

int fd_p;
int fd_org;
int fd_new;
const char * file1;
const char * file2;
const char * file3;


typedef struct {
uint32_t magic;
uint8_t h_version;//0x01
uint8_t d_version;
uint16_t count; //number of 
uint32_t _;
uint32_t __;
}header;

typedef struct {
uint16_t offset;
uint8_t org;
uint8_t new;
}version0;

typedef struct {
uint32_t offset;
uint16_t org;
uint16_t new;
}version1;

int open_read(const char*arr){
	int fd;
	if((fd=open(arr,O_RDONLY))==-1){
		err(2,"couldn't open %s\n",arr);
	}
	return fd;
}

int open_write(const char*arr){
	int fd;
	if((fd=open(arr,O_WRONLY|O_TRUNC|O_CREAT, 0666))==-1){
		err(2,"couldn't open %s\n",arr);
	}
	return fd;
}

void safe_read_header(header* head){
	if(read(fd_p,head,sizeof(header))!=sizeof(header)){
		errx(3,"Couldn't read header correctly\n");
	}
}

void check_header(header* head){
	if(head->magic != 0xEFBEADDE || head->h_version != 0x01 ){
		errx(4,"header->magic or header->header_version is incorrect\n");
	}
}

void copy(int fd, int fd_to){
	char a;
	int bytes;
	//could fork
	while((bytes=read(fd,&a,sizeof(a)))==sizeof(a)){
		if((bytes=write(fd_to,&a,sizeof(a)))!=sizeof(a)){
			err(6,"Couldn't write properly to %s\n",file3);
		}
	}
	if(bytes==-1){
		err(5,"Error occured while reading from %s\n",file2);
	}
}

void equel0(uint8_t r, uint8_t  org){
	if(read(fd_new,&r,sizeof(r))!=sizeof(r)){
		err(10,"Couldn't read from %s in order to check.\n",file3);
	}
	if(r != org){
		errx(11,"Elements are not equel.\n");
	}
}

void equel1(uint16_t r, uint16_t  org){
	if(read(fd_new,&r,sizeof(r))!=sizeof(r)){
		err(10,"Couldn't read from %s in order to check.\n",file3);
	}
	if(r != org){
		errx(11,"Elements are not equel.\n");
	}
}

void safe_write(void* el){
	if(write(fd_new,el,sizeof(*el))!=sizeof(*el)){
		err(13,"Couldn't write/edit to %s.",file3);
	}
}

void editText0(version0 * curr){
	if(lseek(fd_new,curr->offset,SEEK_SET)==-1){
		err(9,"Couldn't lseek from file %s\n",file3);
	}
	uint8_t a;
	equel0(a,curr->org);	
	if(lseek(fd_new,curr->offset,SEEK_SET)==-1){
		err(9,"After check for equel couldn't lseek from file %s.\n",file3);
	}	
	safe_write(&curr->new);
}

void editText1(version1 * curr){
	if(lseek(fd_new,curr->offset,SEEK_SET)==-1){
		err(9,"Couldn't lseek from file %s\n",file3);
	}
	uint16_t a;
	equel1(a,curr->org);	
	if(lseek(fd_new,curr->offset,SEEK_SET)==-1){
		err(9,"After check for equel couldn't lseek from file %s.\n",file3);
	}	
	safe_write(&curr->new);
}

void read_version1(uint16_t count){
	version1 v;
	for(int i=0;i<count; i++){
		if(read(fd_p,&v,sizeof(v))!=sizeof(v)){
			err(8,"Couldn't read correctly struct version1 from %s\n",file1);
		}
		editText1(&v);
	}
}

void read_version0(uint16_t count){
	version0 v;
	for(int i=0;i<count; i++){
		if(read(fd_p,&v,sizeof(v))!=sizeof(v)){
			err(8,"Couldn't read correctly struct version0 from %s\n",file1);
		}
		editText0(&v);
	}
}

void find_version(header* head){
	if(head->d_version == 0x00){
		read_version0(head->count);
	}else if(head->d_version == 0x01){
		read_version1(head->count);
	}
	else {
		errx(7,"Data version from header is invalid\n");
	}
	
}

int main(int argc, char ** argv){
	if(argc != 4 ){
		errx(1,"invalid number of arguments\n");
	}
	file1=argv[1];
	file2=argv[2];
	file3=argv[3];
	fd_p=open_read(argv[1]);
	fd_org=open_read(argv[2]);
	fd_new=open_write(argv[3]);

	header head;
	safe_read_header(&head);
	check_header(&head);
	copy(fd_org,fd_new);
	find_version(&head);
	close(fd_p);
	close(fd_org);
	close(fd_new);

}
