#include "../../aoc_tools.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <map>
using namespace std;

vector<pair<int,int>> neighbours(int i, int j){
   vector<pair<int,int>> dx {{
      {-1,0}, {1,0}, {0,1}, {0,-1}, {1,1}, {-1,-1}, {1,-1}, {-1,1}
   }};
   vector<pair<int,int>> ret(8);
   transform(dx.begin(), dx.end(), ret.begin(), [i,j](auto p){
      return make_pair(p.first+i,p.second+j);
      });
   return ret;
}


map<pair<int,int>, vector<int>> gears;
bool hasAdjSymbol(int i, int js, int je, const vector<string>& arr, string num){
   vector<int> range(je-js+1);
   iota(range.begin(), range.end(), js);
   int R = arr.size();
   int C = arr.front().size();
   return any_of(range.begin(), range.end(), [&](const int j){
         auto n = neighbours(i,j);
         return any_of(n.begin(), n.end(), [&](auto p){
               auto [x,y] = p;
               if(x >= 0 && x < R && y >= 0 && y < C){
                  auto c = arr[x][y];
                  // This if statement is for p2
                  if(c == '*'){
                     gears[{x,y}].push_back(stoi(num));
                  }
                  return c != '.' && !isnumber(c);
               }
               return false;
         });
   });
}

vector<int> partNumbers(const vector<string>& arr){
   vector<int> ret;
   int R = arr.size();
   int C = arr.front().size();
   for(size_t i = 0; i < R; i++){
      for(size_t j = 0; j < C; j++){
         string num = "";
         while(isnumber(arr[i][j])){
            num.push_back(arr[i][j]);
            j++;
         }
         if(num.size() && hasAdjSymbol(i, j-num.size(), j-1, arr, num)){
            ret.push_back(stoi(num));
         }
      }
   }
   return ret;
}

int gearScore(){
   auto lambda = [](int left, auto p){
      auto& [_,v] = p;
      if(v.size() == 2){
         return left + v.front() * v.back();
      }
      return left;
   };
   return accumulate(gears.begin(), gears.end(), 0, lambda);
}

int main(){
   auto arr = AOC::getLines();
   auto p1Numbers = partNumbers(arr);
   auto p1Res = accumulate(p1Numbers.begin(), p1Numbers.end(), 0);
   auto p2Res = gearScore();
   cout << "PartOne: " << p1Res << endl;
   cout << "PartTwo: " << p2Res << endl;
}
