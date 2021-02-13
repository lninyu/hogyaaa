/* mel : Sat Feb 13 17:00:17 UTC 2021 */
#include <iostream>
#include <string>

using namespace std;

string name;

int main(){
  cout << "name:";
  cin >> name;
  if(name == "unko" || name == "unti"){
    puts(" ____________");
    puts("/            \\");
    puts("| hello unko |");
    puts("\\  __________/");
    puts(" |/");
    puts("💩");
  }else{
    cout << "hello " << name << endl;
  }
  return 0;
}