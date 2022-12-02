#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <array>

int wins{0}, losses{0}, draws{0};

std::array<std::string, 3> signs {"Rock", "Paper", "Scissor"};

const std::string filepath {"/home/lukas/prog/AdventOfCode22/day2/main/input"};

int CalcOutcome(char opponent, char player) {
  int res{0};
  int player_num{static_cast<int>(player) - 87};
  int opponent_num{static_cast<int>(opponent) - 64};
  res = player_num;
  int game{opponent_num - player_num};
  std::set<int> winning{2,-1,};
  std::set<int> losing{-2,1};
  if (winning.find(game) != winning.end()){
    res += 6;
    wins++;
  }
  else if (losing.find(game) != losing.end()){
    losses++;
  }
  else if(game == 0){
    res += 3;
    draws++;
  }

  return res;
}

int main(){

  std::ifstream fs{filepath};
  int res{0};
  char players_choice, opponents_choice;

  while(fs >> opponents_choice >> players_choice) {
   res += CalcOutcome(opponents_choice, players_choice);
  }
  
  std::cout << "Result: "  << res << ". Wins: " << wins << ", losses: " << losses << ", draws: " << draws << ", sum: " << wins+losses+draws << std::endl;

  return 0;
}
