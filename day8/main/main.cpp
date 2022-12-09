#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day8/main/input"};

using TreeLine = std::vector<int>;
using TreeMap = std::vector<TreeLine>;

int ViewDistLeft(TreeMap &map, int pos_x, int pos_y) {
  if (pos_x == 0)
    return 0;
  else {
    int res{0};
    int current_height{map[pos_y][pos_x]};

    for (int i = pos_x - 1; i >= 0; --i) {
      ++res;
      if (map[pos_y][i] >= current_height)
        break;
    }
    return res;
  }
}

int ViewDistRight(TreeMap &map, int pos_x, int pos_y) {
  if (pos_x == map[pos_y].size() - 1)
    return 0;
  else {
    int res{0};
    int current_height{map[pos_y][pos_x]};
    for (int i = pos_x + 1; i < map[pos_y].size(); ++i) {
      ++res;
      if (map[pos_y][i] >= current_height)
        break;
    }
    return res;
  }
}

int ViewDistUp(TreeMap &map, int pos_x, int pos_y) {
  if (pos_y == 0)
    return 0;
  else {
    int res{0};
    int current_height{map[pos_y][pos_x]};

    for (int i = pos_y - 1; i >= 0; --i) {
      ++res;
      if (map[i][pos_x] >= current_height)
        break;
    }
    return res;
  }
}

int ViewDistDown(TreeMap &map, int pos_x, int pos_y) {
  if (pos_y == map.size() - 1)
    return 0;
  else {
    int res{0};
    int current_height{map[pos_y][pos_x]};

    for (int i = pos_y + 1; i < map.size(); ++i) {
      ++res;
      if (map[i][pos_x] >= current_height)
        break;
    }
    return res;
  }
}

int ScenicScore(TreeMap &map, int pos_x, int pos_y) {
  int res{1};
  res *= ViewDistLeft(map, pos_x, pos_y);
  res *= ViewDistRight(map, pos_x, pos_y);
  res *= ViewDistUp(map, pos_x, pos_y);
  res *= ViewDistDown(map, pos_x, pos_y);
  return res;
}

TreeLine StrToTreeLine(std::string str) {
  TreeLine tl;
  for (auto c : str) {
    tl.push_back(c - 48);
  }
  return tl;
}

int main() {

  std::ifstream fs{filepath};
  std::string line;
  TreeMap map;
  int res{0};

  while (fs >> line) {
    auto tl = StrToTreeLine(line);
    map.push_back(tl);
  }

  for (int y = 0; y < map.size(); ++y) {
    for (int x = 0; x < map[y].size(); ++x) {
      int tmp_res = ScenicScore(map, x, y);
      if (tmp_res > res)
        res = tmp_res;
    }
  }

  std::cout << "Result: " << res << std::endl;

  return 0;
}
