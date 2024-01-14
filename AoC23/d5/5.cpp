#include "../../aoc_tools.hpp"
#include <vector>
#include <utility>
#include <queue>
#include <map>
#include <numeric>
#include <algorithm>
#include <limits>

using namespace std;
using ll = long long;


/*
 Quite tricky parse for this input, my idea is to parse the transformations
 such that one transform is one element in a vector. Where the transform itself
 has a vector of candidates, where one candidate is a vector of the three elements:
 [dest,source,range]
*/

using trans = vector<vector<ll>>;
using transMap = vector<trans>;
pair<vector<ll>, transMap>  parse(vector<string> lines){
   vector<ll> seeds;
   transMap rest;
   trans temp;
   regex re("(\\d+)");
   for(auto line : lines){
      // Get the seeds line
      if(seeds.size() == 0){
         seeds = AOC::findAll<ll>(re, line);
      }
      // When we have seeds, we start with the transformations
      else{
         // If we have an empty line, store the transform in the
         // output vector
         if(line.size() == 0){
            if(temp.size() > 0){
               rest.push_back(temp);
               temp.clear();
            }
         }
         else{
            auto nums = AOC::findAll<ll>(re, line);
            // This is not a text line
            if(nums.size() > 0){
               temp.push_back(nums);
            }
         }
      }
   }
   // Since the file dont end with an empty line, we have to
   // add the last transformation here.
   if(temp.size()){
      rest.push_back(temp);
   }
   return {seeds,rest};
}


ll transStep(const ll seed, const trans& t){
   for(const auto& candidate : t){
      auto dest = candidate.front();
      auto source = candidate[1];
      auto range = candidate.back();
      if(source <= seed && seed < source+range){
         return dest + seed - source;
      }
   }
   return seed;
}


ll transformSeed(ll seed, const transMap& map){
   for(const auto& t : map){
      seed = transStep(seed, t);
   }
   return seed;
}

ll solvePartOne(vector<ll> seeds, const transMap& map){
   transform(seeds.begin(), seeds.end(),seeds.begin(), [&](auto seed){
         return transformSeed(seed, map);
   });
   return *min_element(seeds.begin(), seeds.end());
}

/* In order to solve the second part efficiently we have to think about the seeds
 as ranges rather than individual elements. Except for that, it is quite similar to the first tasks.
 In the first task we iterated the posible candidates for a seed and in the end we had one out of two
 outcome, the seeds was either inside the source of any of the candidates or not. It the same approach here,
 but we have to consider [low,high] instead of a value.
 This will lead to more complex cases than just inside or outside. We can end up with any combination
 of inside/outside for both low and high:
 1, low inside, high outside.
 2, low outside, high inside.
 3, both low and high inside.
 4, both low and high outside.

 1-3 are trivial, we just have to move the parts of the range that are inside
 to the next transformation, modify [high,low] so we cover the seeds that were
 not inside the source range, and continue searching other candidates.

 4 is a bit trickier. The issue with this case is that the range will be split:
          low------|--------------------|--------high
                   h1    source range   l1

 consider the above figure. We send everything inside the source range to the next
 transform. But then we have to new ranges that still has to be processed for the
 current transformation. So instead of sending them to the next transform, we will
 have to iterate the same transformation again for these two new ranges.
 The two new ranges are [low,h1-1], [l1+1, high]
 So how do we code this?

 We have two options, either we store all states (low,high,index) in a queue
 and iterate until we are done. Or we do the same thing recursively.
 I Personally like the recursion more for these kinds of tasks as I think
 it is easier to imagine and also to write the logic.
*/

bool clamped(const ll low, const ll val, const ll high){
   return val >= low && val <= high;
}

ll transformRange(ll low, ll high, ll transIdx, const transMap& map) {
   if(transIdx == map.size()){
      return low;
   }
   ll ret = numeric_limits<ll>::max();
   const auto& curTrans = map[transIdx];
   for(const auto& candidate : curTrans){
      auto dest = candidate.front();
      auto source = candidate[1];
      auto range = candidate.back();
      auto sourceEnd = source + range - 1;

      // low is outside, high is inside source range
      if(low < source && clamped(source, high, sourceEnd)){
         auto newHigh = dest + high - source;
         ret = min(ret, transformRange(dest, newHigh, transIdx+1, map));
         high = source-1;
      }
      // both low and high are inside source range
      else if(clamped(source, low, sourceEnd) && clamped(source, high, sourceEnd)){
         auto newLow = dest + low - source;
         auto newHigh = dest + high - source;
         ret = min(ret, transformRange(newLow, newHigh, transIdx+1, map));
         // This range is done
         low = 0;
         high = -1;
      }
      // Low is inside, high is outside source range
      else if(clamped(source, low, sourceEnd) && high > sourceEnd){
         auto newLow = dest + low - source;
         ret = min(ret, transformRange(newLow, dest+range-1, transIdx+1, map));
         low = sourceEnd+1;
      }
      // The complicated case: Low is lower and high is higher than the source range
      // Send the whole range to the next step, rerun the two ends, below and above again
      else if(low < source && high > sourceEnd){
         // Send the whole range
         ret = min(ret, transformRange(dest, dest+range-1, transIdx+1, map));
         // rerun the part outside on the lower end
         ret = min(ret, transformRange(low, source-1, transIdx, map));
         // rerun the part outside on the above end
         ret = min(ret, transformRange(sourceEnd+1, high, transIdx, map));
      }
      // We are done for this range
      if(low > high){
         break;
      }
   }
   // If high is still greater than low, that means that we didnt find any tranformation
   // for that remaining range. According to the task, they should be passed as they are to
   // The next step.
   if(low < high){
      ret = min(ret, transformRange(low, high, transIdx+1, map));
   }
   return ret;
}

ll solvePartTwo(const vector<ll>& seeds, const transMap& map){
   ll winner = numeric_limits<ll>::max();
   for(auto i = 0; i < seeds.size(); i+=2){
      auto low = seeds[i];
      auto high = low + seeds[i+1];
      auto lowLocation = transformRange(low,high,0,map);
      winner = min(winner, lowLocation);
   }
   return winner;
}


int main(){
   auto lines = AOC::getLines();
   auto [seeds, maps] = parse(lines);
   cout << "PartOne: " << solvePartOne(seeds, maps) << endl;
   cout << "PartTwo: " << solvePartTwo(seeds, maps) << endl;
}
