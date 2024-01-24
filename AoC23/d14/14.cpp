#include "../../aoc_tools.hpp"
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <set>

using namespace std;

enum class TILT{
   NORTH = 1,
   EAST = 2,
   SOUTH = 3,
   WEST = 4
};

vector<string> parse(){
   auto lines = AOC::getLines();
   return lines;
}

void tiltNorth(vector<string>& map){
   size_t R = map.size();
   size_t C = map.front().size();
   for(int i = 0; i < R; i++){
      for(int j = 0; j < C; j++){
         if(map[i][j] == 'O'){
            int idx = i;
            while(idx > 0 && map[idx-1][j] == '.'){
               map[idx-1][j] = 'O';
               map[idx][j] = '.';
               idx--;
            }
         }
      }
   }
}

void tiltEast(vector<string>& map){
   size_t R = map.size();
   size_t C = map.front().size();
   for(int i = 0; i < R; i++){
      for(int j = C-1; j>= 0; j--){
         if(map[i][j] == 'O'){
            int idx = j;
            while(idx < C-1 && map[i][idx+1] == '.'){
               map[i][idx+1] = 'O';
               map[i][idx] = '.';
               idx++;
            }
         }
      }
   }
}

void tiltSouth(vector<string>& map){
   size_t R = map.size();
   size_t C = map.front().size();
   for(int i = R-1; i >= 0; i--){
      for(int j = 0; j < C; j++){
         if(map[i][j] == 'O'){
            int idx = i;
            while(idx < R-1 && map[idx+1][j] == '.'){
               map[idx+1][j] = 'O';
               map[idx][j] = '.';
               idx++;
            }
         }
      }
   }
}

void tiltWest(vector<string>& map){
   size_t R = map.size();
   size_t C = map.front().size();
   for(int i = 0; i < R; i++){
      for(int j = 0; j < C; j++){
         if(map[i][j] == 'O'){
            int idx = j;
            while(idx > 0 && map[i][idx-1] == '.'){
               map[i][idx-1] = 'O';
               map[i][idx] = '.';
               idx--;
            }
         }
      }
   }
}

int countScore(const vector<string>& map){
   int score = 0;
   for(int i = 0, s = map.size(); i < map.size(); i++, s--){
      const auto& row = map[i];
      score += count(row.begin(), row.end(), 'O') * s;
   }
   return score;
}

int solvePartOne(vector<string> map){
   tiltNorth(map);
   return countScore(map);
}

void cycle(vector<string>& map){
   tiltNorth(map);
   tiltWest(map);
   tiltSouth(map);
   tiltEast(map);
}

int solvePartTwo(vector<string>& map){
   unordered_map<string,int> seen;
   for(int i = 1;;i++){
      cycle(map);
      // Use something to hash the score map at the end of a cycle
      auto str = accumulate(map.begin(), map.end(), string());

      // When we see the same string for the third time, we can be confident that
      // we have enetered the cycle, and all the hashes that are part of the cycle
      // shoud also have been seen twice.
      if(seen[str] == 2){
         auto cnt = count_if(seen.begin(), seen.end(), [](const auto& p){
            return p.second == 2;
         });

         // Check how many hashes we have in the cycle and and subtract the time it takes
         // to enter the cycle from the target cycle. The reminder will be the number of more
         // cycles we have to make in order to align the cycle with the target cycle.
         int mod = (1000000000-i) % cnt;
         int res = 0;
         for(int j = 0; j < mod; j++){
            cycle(map);
         }
         return countScore(map);
      }
      seen[str]++;
   }
   cerr << "Should never happen if the problem is solvable" << endl;
   exit(1);
}

int main(){
   auto map = parse();
   auto resP1 = solvePartOne(map);
   auto resP2 = solvePartTwo(map);
   cout << "PartOne: " << resP1 << endl;
   cout << "PartTwo: " << resP2 << endl;
}
