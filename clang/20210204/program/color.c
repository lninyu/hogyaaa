/*
 * todo:utf-8
 * todo:output(2-7)
 * todo:012    012
 *     :345 -> 123
 *     :678    234
 *
 * tree|./$0
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ESC 0x1B
#define FG 38
#define BG 48
#define M 256

void output();
void usage();

char data;
int r=255, g=0, b=0, ca=0, cm=0, temp=0;

int main(int argc, char arg){
  if(argc==1 && !isatty(0)){
    output();
  }else if(argc==2){
    usage();
  }else{
    exit(0);
  }
}

void output(){
  while((data = fgetc(stdin)) != EOF){
    if(b<=0 && r>=M-1){g++;}
    if(b<=0 && g>=M-1){r--;}
    if(r<=0 && g>=M-1){b++;}
    if(r<=0 && b>=M-1){g--;}
    if(g<=0 && b>=M-1){r++;}
    if(g<=0 && r>=M-1){b--;}
    printf("%c[%d;2;%d;%d;%dm", ESC, FG, r*256/M, g*256/M, b*256/M);
    //printf("%c[%d;2;%d;%d;%dm", ESC, BG, r*256/M, g*256/M, b*256/M);
    printf("%c", data);
  }
}

void usage(){
  puts("usage : lol [-fb ground] [1-8]");
  puts("        foo bar | lol");
}