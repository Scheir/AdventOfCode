#include "../../aoc_tools.hpp"
#include <regex>
#include <vector>
#include <numeric>
#include <functional>

using namespace std;
using ll = long long;

vector<vector<ll>> parse(){
   vector<vector<ll>> stories;
   auto lines = AOC::getLines();
   regex re("(-?\\d+)");
   for(auto line : lines){
      stories.push_back(AOC::findAll<ll>(re, line));
   }
   return stories;
}

vector<vector<ll>> buildPyramid(const vector<ll>& story){
   vector<vector<ll>> rows;
   rows.push_back(story);
   vector<ll> cur = rows.front();

   // Build the pyramid
   while(any_of(cur.begin(), cur.end(), [](const auto& v){
            return v != 0;}))
   {
      vector<ll> next;
      for(int i = 0; i < cur.size()-1; i++){
         next.push_back(cur[i+1] - cur[i]);
      }
      rows.push_back(next);
      cur = rows.back();
   }
   return rows;
}

pair<ll,ll> predictNextValue(const vector<vector<ll>>& pyramid){
   ll next {0};
   ll prev {0};
   for(int i = pyramid.size() - 1; i >= 0; i--){
      next = next - pyramid[i].back();
      prev = pyramid[i].front() - prev;
   }
   return {next,prev};
}

pair<ll,ll> solveStory(const vector<ll>& story){
   auto pyramids = buildPyramid(story);
   return predictNextValue(pyramids);
}

using namespace std::placeholders;
pair<ll,ll> partOne(const vector<vector<ll>>& stories){
   auto lambda = [](int left, const auto& right, bool p1){
      if(p1){
         return left + solveStory(right).first;
      }
      return left + solveStory(right).second;
   };

   auto p1Lambda = bind(lambda, _1, _2, true);
   auto p2Lambda = bind(lambda, _1, _2, false);
   ll p1 = abs(accumulate(stories.begin(), stories.end(), 0, p1Lambda));
   ll p2 = abs(accumulate(stories.begin(), stories.end(), 0, p2Lambda));
   return {p1,p2};
}

int main(){
   auto stories = parse();
   const auto [resP1, resP2] = partOne(stories);
   cout << "PartOne: " << resP1 << endl;
   cout << "PartTwo: " << resP2 << endl;
}
