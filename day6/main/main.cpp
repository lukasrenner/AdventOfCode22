#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day6/main/input"};

int main() {

  std::ifstream fs{filepath};
  int count{0};
  std::string line;
  char input;
  int duplicates{0};
  std::list<char> last_chars;
  std::map<char, uint8_t> char_map;

  while (fs >> input) {
    ++count;
    // add next char
    line.push_back(input);
    auto it = char_map.find(input);
    if (it != char_map.end()) {
      (it->second)++;
      ++duplicates;
    } else {
      char_map.insert(std::make_pair(input, 1));
    }
    // remove current char - 4
    if (count > 4) {
      char rem_char = *(line.end() - 5);
      auto rem_it = char_map.find(rem_char);

      if (rem_it->second == 1) {
        char_map.erase(rem_char);
      } else {
        --duplicates;
        --(rem_it->second);
      }
      if (duplicates == 0)
        break;
    }
  }

  std::cout << "Result: " << count << std::endl;

  return 0;
}
