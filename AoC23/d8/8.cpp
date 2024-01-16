#include "../../aoc_tools.hpp"
#include <vector>
#include <map> #include <cassert>
#include <functional>
#include <numeric>

using namespace std;
using ll = long long;
using network = map<string,pair<string,string>>;

pair<string, map<string,pair<string,string>>> parse(){
   auto lines = AOC::getLines();
   string ops;
   regex re("(\\w+)");
   network m;
   for(auto line : lines){
      if(ops.size() == 0){
         ops = line;
      }
      else if(line.size() == 0){
         continue;
      }
      else{
         auto words = AOC::findAll<string>(re, line);
         assert(words.size() == 3);
         m[words.front()] = {words[1], words.back()};
      }
   }
   return {ops, m};
}

ll runKey(string key, const string& ops, network& ntwrk, function<bool(const string)> f){
   ll idx {0};
   while(!f(key)){
      auto [l,r] = ntwrk[key];
      auto op = ops[idx%ops.size()];
      key = op == 'L' ? l : r;
      idx++;
   }
   return idx;
}

ll solveP1(const string& ops, network& ntwrk){
   auto lambda = [](const string s) -> bool{
      return s == "ZZZ";
   };
   return runKey("AAA", ops, ntwrk, lambda);
}

ll getLcm(const vector<ll>& v){
   return accumulate(v.begin()+1, v.end(), v.front(), [](ll left, ll right){
      return lcm(left,right);
   });
}

ll solveP2(const string& ops, network& ntwrk){
   auto lambda = [](const string s) -> bool {
      return s.back() == 'Z';
   };
   vector<ll> vals;
   for(auto[k,_] : ntwrk){
      if(k.back() == 'A'){
         vals.push_back(runKey(k, ops, ntwrk, lambda));
      }
   }
   return getLcm(vals);
}

int main(){
   auto [ops, ntwrk] = parse();
   auto resP1 = solveP1(ops, ntwrk);
   auto resP2 = solveP2(ops, ntwrk);
   cout << "PartOne: " << resP1 << endl;
   cout << "PartTwo: " << resP2 << endl;
}

