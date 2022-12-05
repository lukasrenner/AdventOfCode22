#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

const std::string filepath {"/home/lukas/prog/AdventOfCode22/day2/main/input"};

int main(){

  std::ifstream fs{filepath};
  int res{0};

  while(fs >> res) {
   
  }
  
  std::cout << "Result: "  << res << std::endl;

  return 0;
}
