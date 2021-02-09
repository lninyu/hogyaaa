#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
//#include<sys/ioctl.h>

#define ESC 0x1B
#define FG 38
#define BG 48
#define SIZE 16777216

void Srb(char *ch);
void colorprint(int Ground, int red, int green, int blue, char str);

int r, g, b, BorF;
char strdata[SIZE];

int main(int argc, char *arg[]){
  if(!strcmp(arg[1], "-r")||!strcmp(arg[1], "--rainbow")){
    if(argc==2 && !isatty(0)){
      while (fgets(strdata, sizeof(strdata), stdin) != NULL){
        Srb(strdata);
      }
    }else if(argc==3 && !isatty(0)){
      printf("no\n");
    }else{
      exit(1);
    }
  }else{
    puts("error");
  }
}

void Srb(char *ch){
r=255;
g=0;
b=0;
BorF=FG;
int i=0;

for(g=0;g<256;g++){colorprint(BorF, r, g, b, ch[i]);i++;}
for(r=255;r>0;r--){colorprint(BorF, r, g, b, ch[i]);i++;}
for(b=0;b<256;b++){colorprint(BorF, r, g, b, ch[i]);i++;}
for(g=255;g>0;g--){colorprint(BorF, r, g, b, ch[i]);i++;}
for(r=0;r<256;r++){colorprint(BorF, r, g, b, ch[i]);i++;}
for(b=255;b>0;b--){colorprint(BorF, r, g, b, ch[i]);i++;}
}

void colorprint(int ground, int red, int green, int blue, char str){
  printf("%c[%d;2;%d;%d;%dm%c", ESC, ground, red, green, blue, str);
}