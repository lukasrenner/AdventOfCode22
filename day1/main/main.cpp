#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <numeric>

#include "day1/elf/elf.hpp"

const std::string filepath {"/home/lukas/prog/AdventOfCode22/day1/main/input"};

int main(){

  std::ifstream fs{filepath};
  std::string line {};
  std::list<int> sums;
  int current_sum{0};
  
  while(std::getline(fs, line)) {
    if(!line.empty())
      current_sum += std::stoi(line);
    else {
      sums.push_back(current_sum);
      current_sum = 0;
      sums.sort();
      if(sums.size()>3)
        sums.pop_front();
    }
  }
  
  std::cout << "Result: "  << std::accumulate(std::begin(sums), std::end(sums), 0) << std::endl;

  return 0;
}
