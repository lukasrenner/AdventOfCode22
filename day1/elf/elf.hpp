#ifndef ELF_HPP
#define ELF_HPP

#include <list>
#include <numeric>

struct Elf {

  Elf(std::list<int> l) : items_{l} {}

  int GetTotalCalories() {
    return std::accumulate(items_.begin(), items_.end(), 0);
  }
  
  std::list<int> items_;

};

#endif
