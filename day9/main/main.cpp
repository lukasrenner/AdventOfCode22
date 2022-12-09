#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day9/main/input"};

using PositionSet = std::set<std::pair<int, int>>;

struct Point {
  int pos_x{0};
  int pos_y{0};
};

bool IsAdjacentOrSame(const Point &p1, const Point &p2) {
  int diff_x = p2.pos_x - p1.pos_x;
  int diff_y = p2.pos_y - p1.pos_y;
  return ((std::abs(diff_x) <= 1) && (std::abs(diff_y) <= 1));
}

void UpdateTail(Point &head, Point &tail, PositionSet &positions_visited) {

  if (IsAdjacentOrSame(head, tail))
    return;
  else {
    int diff_x = head.pos_x - tail.pos_x;
    int diff_y = head.pos_y - tail.pos_y;
    // move right
    if (diff_x > 0 && diff_y == 0) {
      ++tail.pos_x;
    }
    // move up right
    else if (diff_x > 0 && diff_y > 0) {
      ++tail.pos_x;
      ++tail.pos_y;
    }
    // move up
    else if (diff_x == 0 && diff_y > 0) {
      ++tail.pos_y;
    }
    // move up left
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
  positions_visited.insert(std::make_pair(tail.pos_x, tail.pos_y));
}

void MakeMoves(Point &head, Point &tail, char dir, int num_steps,
               PositionSet &positions_visited) {
  for (int i = 0; i < num_steps; ++i) {
    switch (dir) {
    case 'U':
      ++head.pos_y;
      // std::cout << "Moving head up" << std::endl;
      break;
    case 'D':
      --head.pos_y;
      break;
    case 'L':
      --head.pos_x;
      break;
    case 'R':
      ++head.pos_x;
      break;
    }
    UpdateTail(head, tail, positions_visited);
  }
}

int main() {

  std::ifstream fs{filepath};
  PositionSet positions_visited;
  Point head, tail;
  char dir;
  int num_steps;

  positions_visited.insert(std::make_pair(0, 0));

  while (fs >> dir >> num_steps) {
    MakeMoves(head, tail, dir, num_steps, positions_visited);
  }

  std::cout << "Result: " << positions_visited.size() << std::endl;

  return 0;
}
