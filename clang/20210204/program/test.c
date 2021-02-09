#include<stdio.h>
#include<stdlib.h>

#define ESC 0x1B

int main(int argc, char *arg[]){
  for(int loop=232;loop<256;loop++){
    for(int loop=255;loop>231;loop--){
      printf("%c[38;5;%dma", ESC, loop);
    }
    exit(0);
  }
}