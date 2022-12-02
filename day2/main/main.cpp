#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <array>

const std::string filepath {"/home/lukas/prog/AdventOfCode22/day2/main/input"};

std::array<std::string, 3> outcomes {"loss", "draw", "win"};
std::array<std::string, 3> signs {"Rock", "Paper", "Scissors"};

int CalcOutcome(char opponent, char outcome) {
  int res{0};
  int outcome_num{static_cast<int>(outcome) - 88};
  int opponent_num{static_cast<int>(opponent) - 65};
  res = outcome_num*3;
  if(outcome_num == 1)
    res += opponent_num+1;
  else if(outcome_num == 0){
    if(opponent_num == 0)
      res += 3;
    else
      res += ((opponent_num - 1)%3)+1;
  }
   else if(outcome_num == 2)
      res += ((opponent_num + 1)%3)+1;
  return res;
}

int main(){

  std::ifstream fs{filepath};
  int res{0};
  char opponents_choice, desired_outcome;

  while(fs >> opponents_choice >> desired_outcome) {
   res += CalcOutcome(opponents_choice, desired_outcome);
  }
  
  std::cout << "Result: "  << res << std::endl;

  return 0;
}
