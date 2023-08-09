#include <err.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
void safeWrite(char h){
	if(write(1,&h,sizeof(char))==-1){
			err(2,"error writing to stdout\n");
	}
}
void erase(int f, char *sym, char *sym2){
	int len=strlen(sym);
	int s,e;
	if (sym[0]=='\''){
		s=1;
		e=len-1;
	}else {
		s=0;
		e=len;
	}
	char curr,last='\0';
	int bytes;
	bool check=false;
	while ((bytes=read(0, &curr, sizeof(char)))){
		int start=s,end=e;
		if(f==0){//delete
			for(start;start<end;start++){
				if(curr==sym[start]){
					check=true;
					break;
				}
			}
		}else if (f==1){//tr
			for(start;start<end;start++){
				if(curr==sym[start]){
					if(last!=curr){
						break;
					}check=true;
				}
			}
			if(!check){
				check=false;
				safeWrite(curr);
				last=curr;
			}
			check=false;
			continue;
		}else {//swap
			for(start;start<end;start++){
				if(curr==sym[start]){
					safeWrite(sym2[start]);
					check=true;
					break;
				}
			}
			if(check){
				check=false;
				continue;
			}
		}
		if(check){
			check=false;
			continue;
		}		
		safeWrite(curr);
	}
	if (bytes==-1){
		err(1,"couldn't read from stdin\n");
	}
}

int main(int argc, char **argv){
	if (argc<2 || argc >3){
		errx(1,"invalid number of arguments\n");
	}
	if(strcmp(argv[1],"-d")==0){
		erase(0,argv[2],argv[2]);
	}else if(strcmp(argv[1],"-s")==0){
		erase(1,argv[2],argv[2]);
	}else {
		if(strlen(argv[1])!=strlen(argv[2])){
			errx(3,"argument 2 and argument 3 is not equel length\n");
		}
		erase(2,argv[1],argv[2]);
	}
}
