#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string filepath{"/home/lukas/prog/AdventOfCode22/day10/main/input"};

enum OpCode { kNoop, kAddx };

struct Instruction {
  OpCode op;
  int arg;
};

struct CPU {
  int cycle{0};
  int regX{1};
  std::vector<int> regValueInTime{};

  CPU() { regValueInTime.reserve(2500); }

  void ExecInstruction(Instruction instruction) {
    regValueInTime.push_back(regX);
    ++cycle;
    switch (instruction.op) {
    case kNoop:
      // std::cout << "Executing noop" << std::endl;
      break;
    case kAddx:
      // std::cout << "Executing addX " << instruction.arg << std::endl;
      regValueInTime.push_back(regX);
      regX += instruction.arg;
      ++cycle;
      break;
    }
  }

  int GetSignalStrength(std::vector<int> cycleTimes) {
    int res{0};
    for (auto time : cycleTimes) {
      res += (regValueInTime[time - 1] * time);
      std::cout << "Signal Strength at cycle " << time << ": "
                << (regValueInTime[time - 1] * time)
                << " (register value: " << regValueInTime[time] << ")"
                << std::endl;
    }
    return res;
  }

  void Draw() {
    for (int i = 0; i < 240; ++i) {
      if ((regValueInTime[i] - 1) <= (i % 40) &&
          (regValueInTime[i] + 1) >= (i % 40)) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
      if ((i + 1) % 40 == 0) {
        std::cout << std::endl;
      }
    }
  }
};

int main() {

  std::ifstream fs{filepath};
  CPU cpu{};
  int res{0};
  std::string line{};

  while (fs >> line) {
    Instruction instruction;
    if (line == "noop") {
      instruction.op = kNoop;
    } else if (line == "addx") {
      int arg;
      fs >> arg;
      instruction.op = kAddx;
      instruction.arg = arg;
    }
    cpu.ExecInstruction(instruction);
  }

  std::vector<int> times{20, 60, 100, 140, 180, 220};
  res = cpu.GetSignalStrength(times);
  cpu.Draw();

  return 0;
}
