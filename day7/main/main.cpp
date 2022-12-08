#include "Node.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day7/main/input"};

int main() {

  std::ifstream fs{filepath};
  int res{0};
  int res2{0};
  std::string line;
  std::regex rgxCd("\\$ cd (.*)");
  std::regex rgxLs("\\$ ls");
  std::regex rgxLsDir("dir (.*)");
  std::regex rgxLsFile("([0-9]+) (.*)");
  std::regex rgx2("move (\\d+) from (\\d) to (\\d)");
  std::regex lastLine(".*1.*");
  std::smatch match;
  Tree tree;

  while (std::getline(fs, line)) {

    // command is "cd"
    if (std::regex_search(line, match, rgxCd)) {
      auto dir = match[1];
      if (dir == "..")
        tree.GoDirUp();
      else if (dir == "/")
        tree.GoToRoot();
      else
        tree.MoveToDir(dir);
    }

    // command is "ls"
    else if (std::regex_search(line, match, rgxLs)) {
      std::cout << "Listing contents of current dir" << std::endl;
      // Nothing else to be done here
    }

    // line is output of ls - here a directory
    else if (std::regex_search(line, match, rgxLsDir)) {
      std::string dir = match[1];
      std::cout << "Adding dir " << dir << std::endl;
      NodePtr nptr = std::make_shared<Node>(Node(0, 0, dir));
      NodeList l{nptr};
      tree.AddNodes(l);
    }

    // line is output of ls - here a file
    else if (std::regex_search(line, match, rgxLsFile)) {
      std::string file = match[2];
      int size = std::stoi(match[1]);
      std::cout << "Adding file " << file << " of size " << size << std::endl;
      NodePtr nptr = std::make_shared<Node>(Node(0, size, file));
      NodeList l{nptr};
      tree.AddNodes(l);
    }
  }

  auto sizes = tree.GetAllDirSizes();
  for (auto s : sizes) {
    if (s < 100000)
      res += s;
  }

  std::cout << "Result of part 1: " << res << std::endl;

  sizes.sort();

  int root_size = sizes.back();
  int unused_space = 70000000 - root_size;
  int min_dir_size = 30000000 - unused_space;
  std::cout << "unused_space: " << unused_space << std::endl;
  std::cout << "space to free: " << min_dir_size << std::endl;

  for (auto s : sizes) {
    if (s >= min_dir_size) {
      res2 = s;
      break;
    }
  }

  std::cout << "Result of part 2: " << res2 << std::endl;

  return 0;
}
