/* mel : Sat Feb 13 21:06:14 UTC 2021 */
#include <iostream>
#include <string>

unsigned int seed = 0;

void usage(){
  puts("usage");
}

void xor32(unsigned int s){
  s ^= s << 13;
  s ^= s >> 17;
  s ^= s << 15;
  printf("%u", s);
}

int main(int argc, char *argv[]){
  switch(argc){
    case 1:
      usage();
      break;
    case 2:
      seed = atoi(argv[1]);
      xor32(seed);
      break;
    case 3:
      seed = atoi(argv[2]);
      if(argv[1] == "-0" || argv[1] == "--xor32"){
        xor32(seed);
      }
      if(argv[1] == "-1" || argv[1] == "--xor64"){}
      if(argv[1] == "-2" || argv[1] == "--xor96"){}
      if(argv[1] == "-3" || argv[1] == "--xor128"){}
      if(argv[1] == "-4" || argv[1] == "--xor256"){}
      break;
  }
  return 0;
}