#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day4/main/input"};

bool RangeContains(std::pair<int, int> r1, std::pair<int, int> r2) {
  return (r2.first >= r1.first && r2.second <= r1.second);
}

bool RangeOverlaps(std::pair<int, int> r1, std::pair<int, int> r2) {
  return (RangeContains(r1, std::make_pair(r2.first, r2.first)) ||
          RangeContains(r1, std::make_pair(r2.second, r2.second)) ||
          RangeContains(r2, std::make_pair(r1.first, r1.first)) ||
          RangeContains(r2, std::make_pair(r1.second, r1.second)));
}

int main() {

  std::ifstream fs{filepath};
  std::string line{};
  int res1{0};
  int res2{0};

  while (fs >> line) {
    std::regex rgx("([0-9]*)-([0-9]*),([0-9]*)-([0-9]*)");
    std::smatch match;
    std::pair<int, int> range1, range2;

    if (std::regex_search(line, match, rgx)) {
      range1 = std::make_pair(std::stoi(match[1]), std::stoi(match[2]));
      range2 = std::make_pair(std::stoi(match[3]), std::stoi(match[4]));
      if (RangeContains(range1, range2) || RangeContains(range2, range1))
        ++res1;
      if (RangeOverlaps(range1, range2))
        ++res2;
    }
  }

  std::cout << "Result for part 1: " << res1 << std::endl;
  std::cout << "Result for part 2: " << res2 << std::endl;

  return 0;
}
