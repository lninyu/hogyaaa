#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(char a[]);
int temp;
int main(int argc, char *arg[]){
	if(!strcmp(arg[1], "-q")||!strcmp(arg[1], "--quantity")){
		temp = atoi(arg[3]);
		if(argc!=4||temp<0){exit(1);}
		for(int a=0;a<temp;a++){
			printf("%s", arg[2]);
		}
		puts("");
	}else if(!strcmp(arg[1], "-e")||!strcmp(arg[1], "--exit")){
		temp=atoi(arg[2]);
		if(argc!=3||temp<0||temp>255){exit(1);}
		exit(temp);
	}else if(!strcmp(arg[1], "-h")||!strcmp(arg[1], "--help")){
		usage(arg[0]);
	}else{exit(0);}
	exit(0);
}

void usage(char a[]){
	puts("usage");
	printf("%s -q \"str\" count\n", a);
	printf("%s -e [0-255]\n", a);
	printf("%s -h\n", a);
	exit(0);
}