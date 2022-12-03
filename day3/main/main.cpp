#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <algorithm>

const std::string filepath {"/home/lukas/prog/AdventOfCode22/day3/main/input"};

int main(){

  std::ifstream fs{filepath};
  std::string line{};
  int res{0};

  while(fs >> line) {
    std::set<char> left(std::begin(line), std::next(line.begin(), line.size()/2));
    std::set<char> right(std::next(line.begin(), line.size()/2), std::end(line));
    std::set<char> diff;
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(diff, diff.begin()));
    char c{*diff.begin()};
    int val;
    if((c < 123) && (c > 96))
      val = c - 96;
    else
      val = c - 64 + 26;

    // std::cout << c << ": " << val << std::endl;
    res += val;  
  }
  
  std::cout << "Result: "  << res << std::endl;

  return 0;
}
