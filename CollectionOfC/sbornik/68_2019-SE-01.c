#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <err.h>
#include <stdbool.h>

const int MAX_SIZE = 16384;
const int MAX_USERS = 2048;
typedef struct{
	uint32_t uid;
	uint16_t _;
	uint16_t __;
	uint32_t start;
	uint32_t end;
}session;
typedef struct {
	uint32_t uid;
	int dur[MAX_SIZE];
	int len=0;
}user;
int cmpfunc (const void * a, const void * b) {
   	return ( *(const int*)b - *(const int *)a );
}
void out(int ds, int all, user *users, int len){
	for(int i=0; i<len; i++){
		if ((user[i].dur[0])*(user[i].dur[0])>(double)ds/(double)all){
			dprintf(1, "uid:%d\nduration:%d",user[i].uid,user[i].dur[0]);
		}
	}
}
void dispersion(int durations, int counter, user *users, int len){
	int powSum=0;
	for(int i=0; i<len; i++){
		qsort(user[i].dur, user[i].len+1, sizeof(int), cmpfunc);
		for(int j=0;j<user[i].len;j++){
			powSum+=((double)user[i].dur[j] - (double)durations/(double)counter)*((double)user[i].dur[j] - (double)durations/(double)counter);
		}
	}
	out(powSum,counter,users,len);
}
void readData(int fd, int * len, user *users){
	session s;
	int bytes;
	int durations,counter;
	while ((bytes=read(fd,&s,sizeof(s)))==sizeof(s)){
		if (s.end < s.start) {
            errx(7, "invalid session interval");
        }
		bool check=true;
		for(int i=0; i< *len;i++){
			if(s.uid==users[i].uid){
				user[i].dur[user[i].len]=s.end-s.start;
				user[i].len+=1;
				check=false;
				break;
			}
		}
		if(check){
		user[*len].uid=s.uid;
		user[*len].dur[user[*len].len]=s.end-s.start;
		user[*len]+=1;
		*len+=1;
		}
		durations+=s.end-s.start;
		counter++;
	}	
	dispersion(duration,counter,users, *len);
}
int main (int argc, char **argv) {
	if (argc!=2){
		errx(1,"invalid number of arguments");
	}
	int fd;
	if((fd=open(argv[1],O_RDONLY))==-1){
		err(2,"couldn,t open file");
	}
	int lenUsers=0;
   	user users[MAX_USERS];
	readData(fd,&lenUsers,users,)

   close(fd);
  
   
}		
