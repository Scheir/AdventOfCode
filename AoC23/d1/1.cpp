#include <iostream>
#include <vector>
#include <regex>
#include <numeric>
#include <functional>
#include <map>
#include "../../aoc_tools.hpp"

using namespace std;
map<string,string> convert {
   {"one","1"},
   {"two", "2"},
   {"three","3"},
   {"four","4"},
   {"five","5"},
   {"six","6"},
   {"seven","7"},
   {"eight","8"},
   {"nine","9"}
};

int solveForLine(string str){
   regex re("\\d");
   vector<string> num;
   smatch m;
   while(regex_search(str,m,re)){
      num.push_back(m[0].str());
      str = m.suffix();
   }
   return stoi(num.front() + num.back());
}

int solveForLineP2(string str){
   regex re("\\d|one|two|three|four|five|six|seven|eight|nine");
   vector<string> num;
   smatch m;
   while(regex_search(str,m,re)){
      auto cur {m[0].str()};
      auto it = convert.find(cur);
      if(auto it = convert.find(cur); it != convert.end()){
         num.push_back(it->second);
         str = cur.back() + m.suffix().str();
      }
      else{
         num.push_back(cur);
         str = m.suffix();
      }
   }

   return stoi(num.front() + num.back());
}

int getRes(function<int(string&)> fun,  vector<string> lines){
   return accumulate(lines.begin(), lines.end(), 0, [&fun](int prev, auto s){
         return prev + fun(s);
         });

}

int main(){
   auto input = getLines();
   cout << "PartOne: " << getRes(solveForLine, input) << endl;
   cout << "PartTwo: " << getRes(solveForLineP2, input) << endl;
}
