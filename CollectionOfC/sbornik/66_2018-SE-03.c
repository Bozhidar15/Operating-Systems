#include <err.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void writeSafe(const char a){
	if(write(1,&a, sizeof(a))!=1){
		err(3,"couldn't write a char on stdout");
	}
}

void writeSymbols(int a, int b){
	int bytes,counter=1;
	char curr;
	while((bytes=read(0,&curr, sizeof(char)))==sizeof(char)){
		if(curr=='\n'){
			writeSafe('\n');
			counter=1;
			continue;
		}
		if(b==-1){
			if (counter==a){
				writeSafe(curr);
			}
		}else {
			if (counter>=a && counter <= b){
				writeSafe(curr);
			}
		}
		counter++;
	}
	
}

void symbol(const char *number){
	if(strlen(number)==1){
		writeSymbols(atoi(&number[0]),-1);
	}else if(strlen(number)==3){//check n>m
		int a=atoi(&number[0]),b=atoi(&number[2]);
		if(a>=b){
			err(5,"invalid second number after -c");
		}
		writeSymbols(a,b);
	}else {
		err(4,"arg after -c is invalid");
	}
}

void fields(char *el, int a, int b){
	int counter=1,bytes;
	char sep= *el, curr;
	while((bytes=read(0,&curr, sizeof(char)))==sizeof(char)){
		if(curr=='\n'){
			writeSafe('\n');
			counter=1;
			continue;
		}
		if(curr==sep){
			counter++;
			continue;
		}
		if(b==-1){
			if (counter==a){
				writeSafe(curr);
			}
		}else {
			if (counter>=a && counter <= b){
				writeSafe(curr);
			}
		}
	}

}

int main(int argc, char **argv){
	if (argc<3 || argc>5){
		err(1,"invalid number of arguments");
	}
	if (strcmp(argv[1],"-c")==0){//symbol
		symbol(argv[2]);
	} else if (strcmp(argv[1],"-d")==0){
		if (argc != 5 || strcmp(argv[3],"-f")!=0||strlen(argv[4])>3){
			err(6,"error in arguments after -d");
		}
		if(strlen(argv[4])==1){
			fields(argv[2],atoi(&argv[4][0]),-1);
		}else if(strlen(argv[4])==3){
			fields(argv[2],atoi(&argv[4][0]),atoi(&argv[4][2]));
		}else{
			err(7,"arg after -f is invalid");
		}
	} else {
		err(2,"unknown parameter");
	}

}
