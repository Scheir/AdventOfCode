#include "../../aoc_tools.hpp"
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;
using card = tuple<int, vector<int>, vector<int>>;

vector<card> parse(){
   vector<card> ret;
   vector<string> lines = AOC::getLines();
   regex re("(\\d+)");
   for(auto& line : lines){
      auto nrRes = AOC::split(line, ":");
      auto num = AOC::findAll<int>(re,nrRes.front()).back();
      auto leftRight = AOC::split(nrRes.back(), "|");
      auto left = AOC::findAll<int>(re, leftRight.front());
      auto right = AOC::findAll<int>(re, leftRight.back());
      ret.push_back({num,left,right});
   }
   return ret;
}

// Used for Part Two
vector<int> scorePerCard;
int partOne(const vector<card>& cards){
   auto lambda = [](int left, const auto& c){
      auto [_,winners,nums] = c;
      auto cnt = count_if(winners.begin(), winners.end(), [&nums](auto w){
            return find(nums.begin(), nums.end(), w) != nums.end();
      });
      auto cur =  cnt ? 0xffff & (1 << (cnt-1)) : 0;
      scorePerCard.push_back(cnt); // used for part two
      return left + cur;
   };
   return accumulate(cards.begin(), cards.end(), 0, lambda);
}

int partTwo(){
   vector<int> score(scorePerCard.size(), 1);
   for(int i = 0; i < score.size(); i++){
      auto s = scorePerCard[i];
      for(auto j = i+1; s > 0 && j < score.size(); j++, s--){
         score[j] += score[i];
      }
   }
   return accumulate(score.begin(), score.end(), 0);
}

int main(){
   auto cards = parse();
   cout << "PartOne: " << partOne(cards) << endl;
   cout << "PartTwo: " << partTwo() << endl;
}
