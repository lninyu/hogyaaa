#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 16777216

void pipe0();
void pipe1();

char str[SIZE];

int main(int argc, char *arg[]){
  pipe0();
  pipe1();
  if(!strcmp(arg[1], "-p")||!strcmp(arg[1], "--pipe")){
    if(argc==2 && !isatty(0)){
      while (fgets(str, sizeof(str), stdin) != NULL){
        printf("%s", str);
      }
    }else{
      exit(1);
    }
  }else{
    puts("error");
  }
}

void pipe0(){
  if(isatty(fileno(stdin))){
    puts("stdin:term");
  }else{
    puts("stdin:pipe");
  }
}

void pipe1(){
  if(isatty(0)){
    puts("stdin:trem");
  }else{
    puts("stdin:pipe");
  }
}