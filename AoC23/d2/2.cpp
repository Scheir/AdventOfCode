#include "../../aoc_tools.hpp"
#include <map>
#include <utility>
#include <regex>
#include <algorithm>
#include <numeric>

using namespace AOC;
using game = pair<int, vector<tuple<int, string>>>;

map<string,int> D {
      {"red",12},
      {"green", 13},
      {"blue", 14}
   };

vector<game> parseInput(vector<string>& lines){
   vector<game> ret;
   regex re("(\\d+) (red|blue|green)");
   for(auto line : lines){
      auto gameNrAndRest = split(line, ":");
      auto spaceAndNr = split(gameNrAndRest.front(), " ");
      auto nr = stoi(spaceAndNr.back());
      ret.push_back({nr, findAll<int,string>(re, gameNrAndRest.back())});
   }
   return ret;
}

int partOne(const vector<game> games){
   auto lambda = [](int left, auto game){
      auto& [num, elems] = game;
      auto b = all_of(elems.begin(), elems.end(), [](auto e){
            auto [cCount, color] = e;
            return D[color] >= cCount;
         });
      return b ? left + num : left;
   };
   return accumulate(games.begin(), games.end(), 0, lambda);
}

int partTwo(const vector<game> games){
   int res {};
   auto mulLambda = [](int left, auto p){
      return left * p.second;
   };
   for(auto [game, elems] : games){
      map<string, int> minNeeded;
      for(auto [num,col] : elems){
         minNeeded[col] = max(minNeeded[col], num);
      }
      res += accumulate(minNeeded.begin(), minNeeded.end(), 1, mulLambda);
   }
   return res;
}

int main(){
   auto lines = getLines();
   auto games = parseInput(lines);
   cout << "PartOne: " << partOne(games) << endl;
   cout << "PartTwo: " << partTwo(games) << endl;
}

