#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day11/main/input"};

enum FuncType { kSelf, kMult, kAdd };

struct Monkey {
  std::vector<int> items;
  int test_num{0};
  int num{0};
  int throw_true{0};
  int throw_false{0};
  int inspections{0};
  FuncType ft;
  int ApplyFunc(int input) {
    int res{input};
    switch (ft) {
    case kSelf:
      res *= res;
      break;
    case kMult:
      res *= num;
      break;
    case kAdd:
      res += num;
      break;
    }
    return res;
  }
};

int main() {

  std::ifstream fs{filepath};
  int res{0};
  std::string line{};
  std::regex rgxMonkey("Monkey ([0-9]+):");
  std::regex rgxStartingItems("([0-9]+)");
  std::regex rgxFuncAdd(".*old \\+ ([0-9]+)");
  std::regex rgxFuncMult(".*old \\* ([0-9]+)");
  std::regex rgxFuncSelf(".*old \\* old");
  std::regex rgxTest(".*divisible by ([0-9]+)");
  std::regex rgxTestTrue(".*true.*([0-9]+)");
  std::regex rgxTestFalse(".*false.*([0-9]+)");
  std::smatch match;

  std::vector<Monkey> monkeys;

  while (std::getline(fs, line)) {
    if (std::regex_search(line, match, rgxMonkey)) {
      // Create monkey here
      Monkey m;
      // starting items
      std::getline(fs, line);
      std::vector<std::string> starting_items(
          std::sregex_token_iterator(line.begin(), line.end(),
                                     rgxStartingItems),
          {});
      for (auto item : starting_items) {
        m.items.push_back(std::stoi(item));
      }
      // operation
      std::getline(fs, line);
      if (std::regex_search(line, match, rgxFuncAdd)) {
        m.ft = kAdd;
        m.num = std::stoi(match[1]);
      } else if (std::regex_search(line, match, rgxFuncMult)) {
        m.ft = kMult;
        m.num = std::stoi(match[1]);
      } else if (std::regex_search(line, match, rgxFuncSelf)) {
        m.ft = kSelf;
      }
      // test
      std::getline(fs, line);
      if (std::regex_search(line, match, rgxTest)) {
        m.test_num = std::stoi(match[1]);
      }
      // throw true
      std::getline(fs, line);
      if (std::regex_search(line, match, rgxTestTrue)) {
        m.throw_true = std::stoi(match[1]);
      }
      // throw false
      std::getline(fs, line);
      if (std::regex_search(line, match, rgxTestFalse)) {
        m.throw_false = std::stoi(match[1]);
      }

      monkeys.push_back(m);
    }
  }

  // loop over 20 rounds
  for (int i = 0; i < 20; ++i) {
    // std::cout << "Starting round " << i << std::endl;
    // loop over monkeys
    for (auto &m : monkeys) {
      // std::cout << "New monkey" << std::endl;
      // loop over items
      auto it = m.items.begin();
      while (it != m.items.end()) {
        m.inspections++;
        // std::cout << "Inspecting item of level " << *it << std::endl;
        int new_level = m.ApplyFunc(*it);
        // std::cout << "Worry level increases to " << new_level << std::endl;
        new_level = std::floor(static_cast<float>(new_level) / 3.0);
        // std::cout << "Monkey is bored, worry level decreases to " <<
        // new_level
        //           << std::endl;
        // test and throw to another monkey
        if (new_level % m.test_num == 0) {
          monkeys[m.throw_true].items.push_back(new_level);
          // std::cout << "Worry level is divisible by " << m.test_num
          //           << ", throwing to monkey " << m.throw_true << std::endl;
        } else {
          monkeys[m.throw_false].items.push_back(new_level);
          // std::cout << "Worry level is NOT divisible by " << m.test_num
          //           << ", throwing to monkey " << m.throw_false << std::endl;
        }
        it = m.items.erase(it);
      }
      // std::cout << std::endl;
    }
    // std::cout << std::endl;
  }
  std::cout << std::endl;

  std::list<int> inspects;

  for (auto &m : monkeys) {
    std::cout << "Monkey inspected " << m.inspections << " items" << std::endl;
    inspects.push_back(m.inspections);
  }

  inspects.sort();
  res = inspects.back();
  inspects.pop_back();
  res *= inspects.back();

  std::cout << "Result: " << res << std::endl;

  return 0;
}
