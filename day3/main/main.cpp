#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <algorithm>
#include <array>

const std::string filepath {"/home/lukas/prog/AdventOfCode22/day3/main/input"};

int main(){

  std::ifstream fs{filepath};
  std::string line{};
  int res{0};
  int count{1};
  std::array<std::set<char>, 3> lines;

  while(fs >> line) {
  
    lines[(count-1)%3] = std::set<char>(std::begin(line), std::end(line));
    if(count % 3 == 0) {
      std::set<char> diff, diff2;
      std::set_intersection(lines[0].begin(), lines[0].end(), lines[1].begin(), lines[1].end(), std::inserter(diff, diff.begin()));
      std::set_intersection(lines[2].begin(), lines[2].end(), diff.begin(), diff.end(), std::inserter(diff2, diff2.begin()));
      char c{*diff2.begin()};
      int val;
      if((c < 123) && (c > 96))
        val = c - 96;
      else
        val = c - 64 + 26;
      
      std::cout << c << ": " << val << std::endl;
      res += val; 
    }

    count++; 
  }
  
  std::cout << "Result: "  << res << std::endl;

  return 0;
}
