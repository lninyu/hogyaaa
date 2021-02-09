#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void err();
void usage();
void box();

int main(int argc, char *argv[]){
	if(argc==1||argc>4){exit(1);}
	if(!strcmp(argv[1], "-h")||!strcmp(argv[1], "--help")){
		err(argc, 2);
		usage();
	}else if(!strcmp(argv[1], "-t")||!strcmp(argv[1], "--thin")){
		err(argc, 4);
		box(0, argv[2], argv[3]);
	}else if(!strcmp(argv[1], "-b")||!strcmp(argv[1], "--bold")){
		err(argc, 4);
		box(7, argv[2], argv[3]);
	}else if(!strcmp(argv[1], "-f")||!strcmp(argv[1], "--fill")){
		err(argc, 4);
		for(int y=0;y<atoi(argv[3]);y++){
			for(int x=0;x<atoi(argv[2]);x++){
				printf("█");
			}
			puts("");
		}
	}else{
		err(argc, 3);
		box(0, argv[1], argv[2]);
	}
	exit(0);
}

void box(int flag, char widthc[], char heightc[]){
	int width = atoi(widthc);
	int height = atoi(heightc);
	char cs[][4] = {"└", "┘", "│", "┌", "┐", "─", " ", "┗", "┛", "┃", "┏", "┓", "━", " "};
	//t:0-6 b:7-13   0    1    2    3    4    5    6

	if(width<2||height<2){
		printf("error:width, height should be at least 2 (%d, %d)\n", width, height);
		exit(1);
	}

	for(int y=1;y<=height;y++){
		for(int x=1;x<=width;x++){
			if(y==1){
				if(x==1){
					printf("%s", cs[3+flag]);
				}else if(x==width){
					printf("%s", cs[4+flag]);
				}else{
					printf("%s", cs[5+flag]);
				}
			}else if(y==height){
				if(x==1){
					printf("%s", cs[0+flag]);
				}else if(x==width){
					printf("%s", cs[1+flag]);
				}else{
					printf("%s", cs[5+flag]);
				}
			}else{
				if(x==1||x==width){
					printf("%s", cs[2+flag]);
				}else{
					printf("%s", cs[6+flag]);
				}
			}
		}
		puts("");
	}
}

void usage(){
	puts("usage  : box [option] width height");
	puts("option : -t --thin  thin line (default)");
	puts("       : -b --bold  bold line");
}

void err(int a, int n){
	if(a!=n){
		printf("error:illegal argument\n      set to %d arguments\n", n-1);
		exit(1);
	}
}