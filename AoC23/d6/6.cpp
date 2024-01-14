#include "../../aoc_tools.hpp"
#include <vector>
#include <regex>
#include <numeric>
#include <functional>

using namespace std;
using ll = unsigned long long;

pair<vector<ll>, vector<ll>> parse(){
   auto lines = AOC::getLines();
   regex re("(\\d+)");
   auto time = AOC::findAll<ll>(re, lines.front());
   auto dist = AOC::findAll<ll>(re, lines.back());
   return {time,dist};
}

ll binarySearch(ll time, ll dist, ll low, ll high, std::function<bool(ll,ll)> f){
   if(low+1 >= high){
      return f(low,high) ? high : low;
   }
   ll mid {low + (high - low) / 2};
   ll reachedDistance {mid*(time-mid)};
   if(f(reachedDistance, dist)){
      return binarySearch(time, dist, mid, high, f);
   }
   else{
      return binarySearch(time, dist, low, mid, f);
   }
}

/*
 * We can find the lower and upper bound of the range which beats
 * the record in O(2*log(n/2)) time using binarysearch.
 *
 * We find the lower bound by searching the range [0, t//2]
 * and the upper bound by searching the range [t//2, t].
 *
 * The binarysearch function will be a bit different for the two
 * cases, as the search space for the lower case starts ouside the record
 * range (T=0) while in the higher case (T=time/2) we start inside the record
 * range. In order to reuse the binarySearch function, this is fixed by passing
 * a callback whch is a binary comparator.
 */
ll partOne(const vector<ll>& time, const vector<ll>& dist){
   ll res = 1;
   for(size_t i = 0; i < time.size(); i++){
      // Find lowest and highest value that beats the record
      auto low = binarySearch(time[i], dist[i], 0, time[i]/2, std::less_equal<ll>());
      auto high = binarySearch(time[i], dist[i], time[i]/2, time[i], std::greater<ll>());
      res *= (high-low+1);
   }
   return res;
}

ll partTwo(const vector<ll>& time, const vector<ll>& dist){
   ll concatTime{stoull(accumulate(time.begin(), time.end(), string(), [](const string& left, const auto right){
            return left+to_string(right);
   }))};
   ll concatDist{stoull(accumulate(dist.begin(), dist.end(), string(), [](const string& left, const auto right){
            return left+to_string(right);
   }))};

   auto low = binarySearch(concatTime, concatDist, 0, concatTime/2, std::less_equal<ll>());
   auto high = binarySearch(concatTime, concatDist, concatTime/2, concatTime, std::greater<ll>());
   return high-low+1;
}

int main(){
   const auto [time, dist] = parse();
   auto resP1 = partOne(time, dist);
   auto resP2 = partTwo(time, dist);
   cout << "PartOne: " << resP1 << endl;
   cout << "PartTwo: " << resP2 << endl;
}

