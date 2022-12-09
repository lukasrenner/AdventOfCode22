#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day8/main/input"};

using TreeLine = std::vector<std::pair<int, bool>>;

int CheckLineLeft(TreeLine &line) {
  int res{0}; // start at 1 for the leftmost tree
  if (line[0].second == false) {
    line[0].second = true;
    ++res;
  }
  int max_height{line[0].first};
  for (size_t i = 1; i < line.size() - 1;
       ++i) { // -1 so we dont check the rightmost tree twice
    if (line[i].first > max_height) {
      max_height = line[i].first;
      if (line[i].second == false) {
        ++res;
        line[i].second = true;
      }
    }
    // std::cout << "maxheight: " << max_height << std::endl;
  }
  // std::cout << "Found " << res << " hits" << std::endl;
  return res;
}

TreeLine StrToTreeLine(std::string str) {
  TreeLine tl;
  for (auto c : str) {
    tl.push_back(std::make_pair(c - 48, false));
  }
  return tl;
}

int CheckLineRight(TreeLine &line) {
  std::reverse(line.begin(), line.end());
  return CheckLineLeft(line);
}

void PrintMap(std::vector<TreeLine> &map) {
  for (auto tl : map) {
    for (auto t : tl) {
      if (t.second)
        std::cout << "X";
      else
        std::cout << t.first;
    }
    std::cout << std::endl;
  }
}

int main() {

  std::ifstream fs{filepath};
  std::string line;
  std::vector<TreeLine> map;
  int res{0};

  while (fs >> line) {
    // std::cout << line << std::endl;
    auto tl = StrToTreeLine(line);
    res += CheckLineLeft(tl);
    res += CheckLineRight(tl);
    map.push_back(tl);
  }

  // make and check vertical lines
  for (size_t x = 1; x < map[0].size() - 1;
       ++x) { // avoid left-most and right-most treelines, they are all visible
              // and considered in the first part
    TreeLine tl;
    for (size_t y = 0; y < map.size(); ++y) {
      tl.push_back(std::make_pair(map[y][x].first, map[y][x].second));
    }

    res += CheckLineLeft(tl);
    res += CheckLineRight(tl);

    // for (auto t : tl) {
    //   if (t.second)
    //     std::cout << "X";
    //   else
    //     std::cout << t.first;
    // }
    // std::cout << std::endl;
  }
  // PrintMap(map);
  std::cout << "Result: " << res << std::endl;

  return 0;
}
