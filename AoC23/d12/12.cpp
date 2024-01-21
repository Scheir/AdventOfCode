#include "../../aoc_tools.hpp"
#include <vector>
#include <utility>
#include <regex>
#include <map>
#include <numeric>
#include <functional>

using namespace std;

using state = tuple<int,int,int>;

vector<pair<string, vector<int>>> parse(){
   auto lines = AOC::getLines();
   vector<pair<string, vector<int>>> ret;
   regex re("(\\d+)");
   for(auto& line : lines){
      auto v = AOC::split(line, " ");
      string s = v.front();
      string rest = v.back();
      vector<int> nums = AOC::findAll<int>(re, rest);
      ret.push_back({s,nums});
   }
   return ret;
}

string getIter(char c){
   if(c == '?')
      return ".#";
   else if(c == '.')
      return ".";
   else if(c == '#')
      return "#";
   else{
      cout << "Failed on char: " << c << endl;
      exit(1);
   }
}

long long solve(const string& str, const vector<int>& groups,
           int idx, int grpIdx, int curGrp, map<state,long long>& DP){
   if(idx == str.size()){
      // Ending with a #
      if(grpIdx == (groups.size() - 1) && curGrp == groups[grpIdx]){
         return 1;
      }
      // Ending with a .
      else if(grpIdx == groups.size()){
         return 1;
      }
      return 0;
   }

   state s {idx, curGrp, grpIdx};
   if(DP.find(s) != DP.end()){
      return DP[s];
   }

   long long ret = 0;
   for(auto c : getIter(str[idx])){
      if(c == '.'){
         // We build a group
         if(curGrp > 0){
            if(curGrp == groups[grpIdx]){
               ret += solve(str, groups, idx+1, grpIdx+1, 0, DP);
            }
            // Current group doesnt match, so end search here
            else{
               ret += 0;
            }
         }
         else{
            ret += solve(str, groups, idx+1, grpIdx, 0, DP);
         }
      }
      else if(c == '#'){
         if(grpIdx < groups.size() && groups[grpIdx] > curGrp){
            ret += solve(str, groups, idx+1, grpIdx, curGrp+1, DP);
         }
      }
   }

   DP[s] = ret;
   return ret;
}

long long solvePartOne(const vector<pair<string,vector<int>>> lines){
   auto lambda = [](long long left, const auto& pair){
      map<state, long long> DP;
      const auto& [s, groups] = pair;
      return left + solve(s, groups, 0, 0, 0, DP);
   };
   return accumulate(lines.begin(), lines.end(), 0, lambda);
}

long long solvePartTwo(const vector<pair<string,vector<int>>> lines){
   auto lambda = [](long long left, const auto& pair){
      map<state, long long> DP;
      const auto& [s, groups] = pair;
      string inString = s;
      vector<int> inVec = groups;
      for(int i = 0; i < 4; i++){
         inString += "?" + s;
         for(const auto& n : groups){
            inVec.push_back(n);
         }
      }
      return left + solve(inString, inVec, 0, 0, 0, DP);
   };
   return accumulate(lines.begin(), lines.end(), 0ll, lambda);
}

int main(){
   auto parsedInput =  parse();
   auto p1Res = solvePartOne(parsedInput);
   auto p2Res = solvePartTwo(parsedInput);
   cout << "PartOne: " << p1Res << endl;
   cout << "PartTwo: " << p2Res << endl;

}
