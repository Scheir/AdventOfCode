#include "../../aoc_tools.hpp"
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

map<char, int> cardValues= {
     {'2', 2},
     {'3', 3},
     {'4', 4},
     {'5', 5},
     {'6', 6},
     {'7', 7},
     {'8', 8},
     {'9', 9},
     {'T', 10},
     {'J', 11},
     {'Q', 12},
     {'K', 13},
     {'A', 14}
 };

enum class HAND{
   high_card = 0,
   pair = 1,
   two_pairs = 2,
   three_of_a_kind = 3,
   full_house = 4,
   four_of_a_kind = 5,
   five_of_a_kind = 6
};

vector<pair<string, int>> parse(){
   auto lines = AOC::getLines();
   vector<pair<string, int>> v;
   regex re("(\\w+) (\\d+)");
   for(const auto& line : lines){
      auto [s,n] = AOC::findAll<string,int>(re, line).front();
      v.push_back({s,n});
   }
   return v;
}


int highestValueCount(const map<char,int>& hand){
   auto maxPair = *max_element(hand.begin(), hand.end(), [](const auto& a, const auto& b){
         return a.second < b.second;
         });
   return maxPair.second;
}

HAND evalHand(const string& hand, bool jokers = false){
   map<char,int> counter;
   for(const auto c : hand){
      counter[c]++;
   }

   int js = 0;
   if(jokers){
      js = counter['J'];
      if(js == 5){
         return HAND::five_of_a_kind;
      }
      counter.erase('J');
   }

   auto maxVal = highestValueCount(counter) + js;


   if(counter.size() == 1){
      return HAND::five_of_a_kind;
   }
   else if(counter.size() == 2){
      if(maxVal == 4){
         return HAND::four_of_a_kind;
      }
      else{
         return HAND::full_house;
      }
   }
   else if(counter.size() == 3){
      if(maxVal == 3){
         return HAND::three_of_a_kind;
      }
      else{
         return HAND::two_pairs;
      }
   }
   else if(counter.size() == 4){
      return HAND::pair;
   }
   else{
      return HAND::high_card;
   }
}
bool handComparator(const pair<string,int>& handAp, const pair<string,int>& handBp, bool jokers){
   string handA = handAp.first;
   string handB = handBp.first;
   auto handAScore = evalHand(handA, jokers);
   auto handBScore = evalHand(handB, jokers);

   if(handAScore != handBScore){
      return handAScore < handBScore;
   }
   for(int i = 0; i < handA.size(); i++){
      auto cardAVal = jokers && handA[i] == 'J' ? 1 : cardValues[handA[i]];
      auto cardBVal = jokers && handB[i] == 'J' ? 1 : cardValues[handB[i]];
      if(cardAVal != cardBVal){
         return cardAVal < cardBVal;
      }
   }
   // Should never happen
   return false;
}

using binaryComp = std::function<bool(const pair<string,int>&, const pair<string,int>&)>;
int solve(vector<pair<string, int>>& hands, binaryComp sortFun){
   sort(hands.begin(), hands.end(), sortFun);
   int res = 0;

   for(int i = 0, s = 1; i < hands.size(); i++, s++){
      const auto& hand = hands[i];
      res += s*hand.second;
   }
   return res;
}

int solveP1(vector<pair<string, int>>& hands){
   auto sortFun = bind(handComparator, placeholders::_1, placeholders::_2, false);
   return solve(hands, sortFun);
}

int solveP2(vector<pair<string, int>>& hands){
   auto sortFun = bind(handComparator, placeholders::_1, placeholders::_2, true);
   return solve(hands, sortFun);
}

int main(){
   auto hands = parse();
   auto p1Res = solveP1(hands);
   auto p2Res = solveP2(hands);
   cout << "PartOne: " << p1Res << endl;
   cout << "PartTwo: " << p2Res << endl;
}

