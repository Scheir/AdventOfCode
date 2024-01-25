#include "../../aoc_tools.hpp"
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>

using namespace std;
using ll = long long;

vector<string> parse(){
   auto line = AOC::getLines().front();
   auto words = AOC::split(line, ",");
   return words;
}

ll hashAlgo(ll left, const string word){
   return left + accumulate(word.begin(), word.end(), 0, [&](ll innerLeft, const char letter){
         innerLeft += static_cast<ll>(letter);
         innerLeft *= 17;
         innerLeft %= 256;
         return innerLeft;
   });
}

ll solvePartOne(const vector<string>& words){
   return accumulate(words.begin(), words.end(), 0ll, hashAlgo);
}

ll charToInt(char c){
   return static_cast<ll>(c-'0');
}

ll countScore(map<int,map<string,pair<ll,ll>>>& boxes){
   ll res = 0;
   for(auto& box : boxes){
      vector<pair<ll,ll>> vp;
      for(const auto p : box.second){
         vp.push_back(p.second);
      }
      sort(vp.begin(), vp.end(), [](const auto a, const auto b){
            return a.second < b.second;
      });
      for(int i = 0; i < vp.size(); i++){
         auto cur = (box.first+1) * (i+1) * vp[i].first;
         res += cur;
      }
   }
   return res;
}

// Since we dont have any option to iterate the lenses in the order
// of insertion in c++ we have to do some hacks where attach the value with
// index of insertion.
// We can with these indices sort the lenses in the boxes to find the order
// of insertion which is needed when we calculate the result.
ll solvePartTwo(const vector<string>& words){
   map<int,map<string, pair<ll,ll>>> boxes;
   int idx = 0;
   for(const auto& word : words){
      bool equal = word.find("=") != string::npos;
      if(equal){
         auto sub = word.substr(0, word.find("="));
         auto label = hashAlgo(0, sub);
         if(boxes[label].contains(sub)){
            boxes[label][sub].first = charToInt(word.back());
         }
         else{
            boxes[label][sub] = {charToInt(word.back()), idx};
         }
      }
      else{
         auto sub = word.substr(0, word.find("-"));
         auto label = hashAlgo(0,sub);
         auto box = boxes[label].erase(sub);
      }
      idx++;
   }
   return countScore(boxes);
}


int main(){
   auto words = parse();
   auto resP1 = solvePartOne(words);
   auto resP2 = solvePartTwo(words);
   cout << "PartOne: " << resP1 << endl;
   cout << "PartTwo: " << resP2 << endl;
}
