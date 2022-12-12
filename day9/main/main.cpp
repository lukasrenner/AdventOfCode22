#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const std::string filepath{"/home/lukas/AdventOfCode22/day9/main/input"};

using PositionSet = std::set<std::pair<int, int>>;

constexpr int kNumKnots{10};

struct Point {
  Point() : pos_x{0}, pos_y{0} {}
  Point(int x, int y) : pos_x{x}, pos_y{y} {}
  int pos_x{0};
  int pos_y{0};

  // bool operator<(const Point &rhs) const {
  //   return ((pos_x < rhs.pos_x) || (pos_y < rhs.pos_y));
  // }
};

bool IsAdjacentOrSame(const Point &p1, const Point &p2) {
  int diff_x = p2.pos_x - p1.pos_x;
  int diff_y = p2.pos_y - p1.pos_y;
  return ((std::abs(diff_x) <= 1) && (std::abs(diff_y) <= 1));
}

void UpdateTail(Point &head, Point &tail) {

  if (IsAdjacentOrSame(head, tail))
    return;
  else {
    int diff_x = head.pos_x - tail.pos_x;
    int diff_y = head.pos_y - tail.pos_y;
    // move right
    if (diff_x > 0 && diff_y == 0) {
      ++(tail.pos_x);
    }
    // move up right
    else if (diff_x > 0 && diff_y > 0) {
      ++tail.pos_x;
      ++tail.pos_y;
    }
    // // move up
    else if (diff_x == 0 && diff_y > 0) {
      ++tail.pos_y;
    }
    // // move up left
    else if (diff_x < 0 && diff_y > 0) {
      --tail.pos_x;
      ++tail.pos_y;
    }
    // move left
    else if (diff_x < 0 && diff_y == 0) {
      --tail.pos_x;
    }
    // move down left
    else if (diff_x < 0 && diff_y < 0) {
      --tail.pos_x;
      --tail.pos_y;
    }
    // move down
    else if (diff_x == 0 && diff_y < 0) {
      --tail.pos_y;
    }
    // move down right
    else if (diff_x > 0 && diff_y < 0) {
      ++tail.pos_x;
      --tail.pos_y;
    }
  }
}

struct Rope {
  PositionSet positions_visited;
  std::map<Point, char> tail_visited_map;
  std::vector<Point> knots;
  int max_x{0};
  int min_x{0};
  int max_y{0};
  int min_y{0};
  Rope() {
    knots.resize(kNumKnots);
    positions_visited.insert(std::make_pair(0, 0));
  }

  PositionSet GetPosVisited() { return positions_visited; }

  void Move(char dir, int num_steps) {

    for (int i = 0; i < num_steps; ++i) {
      switch (dir) {
      case 'U':
        ++knots[0].pos_y;
        break;
      case 'D':
        --knots[0].pos_y;
        break;
      case 'L':
        --knots[0].pos_x;
        break;
      case 'R':
        ++knots[0].pos_x;
        break;
      }

      for (int i = 0; i < kNumKnots - 1; ++i) {
        UpdateTail(knots[i], knots[i + 1]);
        UpdateFieldOfView();
      }

      positions_visited.insert(std::make_pair(knots[kNumKnots - 1].pos_x,
                                              knots[kNumKnots - 1].pos_y));
    }
    Print();
  }

  void UpdateFieldOfView() {
    for (auto &k : knots) {
      if (k.pos_x < min_x)
        min_x = k.pos_x;
      else if (k.pos_x > max_x)
        max_x = k.pos_x;
      if (k.pos_y < min_y)
        min_y = k.pos_y;
      else if (k.pos_y > max_y)
        max_y = k.pos_y;
    }
  }

  void Print() {

    for (int y = max_y + 2; y > min_y - 2; --y) {
      for (int x = min_x - 2; x < max_x + 2; ++x) {
        if (x == 0 && y == 0) {
          std::cout << 's';
          continue;
        }
        bool found(false);
        int count{0};
        for (int i = 0; i < kNumKnots; ++i) {
          // if (positions_visited.find(std::make_pair(x, y)) !=
          //     positions_visited.end()) {
          //   std::cout << 'X';
          //   found = true;
          //   break;
          // }
          if ((knots[i].pos_x == x) && (knots[i].pos_y == y)) {
            std::cout << count;
            found = true;
            break;
          }
          ++count;
        }
        if (!found) {
          std::cout << '.';
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void PrintTail() {

    for (int y = max_y + 2; y > min_y - 2; --y) {
      for (int x = min_x - 2; x < max_x + 2; ++x) {
        if (x == 0 && y == 0) {
          std::cout << 's';
          continue;
        }
        bool found(false);

        for (int i = 0; i < kNumKnots; ++i) {
          if (positions_visited.find(std::make_pair(x, y)) !=
              positions_visited.end()) {
            std::cout << 'X';
            found = true;
            break;
          }
        }
        if (!found) {
          std::cout << '.';
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
};

int main() {

  std::ifstream fs{filepath};
  Rope rope;
  char dir;
  int num_steps;
  while (fs >> dir >> num_steps) {
    rope.Move(dir, num_steps);
  }
  rope.PrintTail();
  std::cout << "Result: " << rope.GetPosVisited().size() << std::endl;

  return 0;
}
