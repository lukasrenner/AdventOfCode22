#ifndef CRATESTACK_HPP
#define CRATESTACK_HPP

#include <list>

using CrateList = std::list<char>;

class CrateStack {
private:
  CrateList crates_;
  char symbol_{};

public:
  CrateStack() = default;
  CrateStack(CrateList l, char s) : crates_{l}, symbol_{s} {}
  void AddCrates(CrateList l) { crates_.splice(crates_.begin(), l); }
  CrateList RemoveCrates(size_t n) {
    CrateList tmp;
    for (size_t i = 0; i < n; ++i) {
      tmp.push_front(crates_.front());
      crates_.pop_front();
    }

    return tmp;
  }
  void AddCrateAtBack(char c) { crates_.push_back(c); }
  size_t GetSize() { return crates_.size(); }
  void Print() {
    for (const auto &c : crates_) {
      std::cout << "[" << c << "]" << std::endl;
    }
    std::cout << ' ' << symbol_ << std::endl;
  }

  char GetTopCrate() { return crates_.front(); }

  void SetSymbol(char s) { symbol_ = s; }
};

void MoveCrates(CrateStack &src, CrateStack &dest, size_t n) {
  dest.AddCrates(src.RemoveCrates(n));
}

#endif