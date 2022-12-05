#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <sstream>
#include <vector>

#include "CrateStack.hpp"

const std::string filepath{"/home/lukas/AdventOfCode22/day5/main/input"};

std::vector<CrateStack> PrepareStacks(const std::string fp) {
  std::ifstream fs{fp};
  std::vector<CrateStack> stacks(9);
  std::string line{};
  std::regex rgx1("(?:\\[([A-Z])\\])|(\\s{4})");
  std::regex rgx2("move (\\d+) from (\\d) to (\\d)");
  std::regex lastLine(".*1.*");
  std::smatch match;

  int n{0};
  for (auto &s : stacks) {
    ++n;
    s.SetSymbol(std::to_string(n)[0]);
  }

  while (true) {
    std::getline(fs, line);
    if (std::regex_search(line, match, lastLine)) {
      break;
    }
    std::vector<std::string> crates(
        std::sregex_token_iterator(line.begin(), line.end(), rgx1), {});
    int pos{0};
    for (auto crate : crates) {
      if (std::isalpha(crate[1])) {
        stacks[pos].AddCrateAtBack(crate[1]);
      }
      ++pos;
    }
  }

  while (std::getline(fs, line)) {

    if (std::regex_search(line, match, rgx2)) {
      MoveCrates(stacks[std::stoi(match[2]) - 1],
                 stacks[std::stoi(match[3]) - 1], std::stoi(match[1]));
    }
  }

  return stacks;
}

int main() {

  int res{0};

  auto stacks = PrepareStacks(filepath);

  std::cout << "Result: ";
  for (auto &stack : stacks) {
    std::cout << stack.GetTopCrate();
  }
  std::cout << std::endl;

  return 0;
}
