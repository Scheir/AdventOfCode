#include "../../aoc_tools.hpp"
#include <algorithm>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>

using namespace std;

vector<string> parse(){
   auto lines = AOC::getLines();
   return lines;
}

vector<pair<int,int>> getGalaxies(const vector<string>& map){
   vector<pair<int,int>> galaxies;
   for(size_t i = 0; i < map.size(); i++){
      for(size_t j = 0; j < map.front().size(); j++){
         if(map[i][j] == '#'){
            galaxies.push_back({i,j});
         }
      }
   }
   return galaxies;
}

vector<int> emptyRows(const vector<string>& map){
   vector<int> rows;
   for(int i = 0; i < map.size(); i++){
      if(none_of(map[i].begin(), map[i].end(), [](const auto c){
         return c == '#';
      })){
         rows.push_back(i);
      }
   }
   return rows;
}

vector<int> emptyCols(const vector<string>& map){
   vector<int> cols;
   for(int j = 0; j < map.front().size(); j++){
      bool galaxy = false;
      for(int i = 0; i < map.size(); i++){
         if(map[i][j] == '#'){
            galaxy = true;
            break;
         }
      }
      if(!galaxy){
         cols.push_back(j);
      }
   }
   return cols;
}

long long manhattan(const pair<int,int>& g1,  pair<int,int>& g2){
   return abs(g1.first - g2.first) + abs(g1.second - g2.second);
}

long long numberOfEmptyRowsAndCols(const vector<int>& rows, const vector<int>& cols,
                             const pair<int,int> g1, const pair<int,int> g2){

   auto lambdaRow = [&](const int row){
      auto l = min(g1.first, g2.first);
      auto h = max(g1.first, g2.first);
      return l < row && row < h;
   };
   auto lambdaCol = [&](const int col){
      auto l = min(g1.second, g2.second);
      auto h = max(g1.second, g2.second);
      return l < col && col < h;
   };
   auto nrRows = count_if(rows.begin(), rows.end(), lambdaRow);
   auto nrCols = count_if(cols.begin(), cols.end(), lambdaCol);
   return nrRows + nrCols;
}



long long solve(const vector<string>& map, long long expansion){
   long long res = 0;
   auto galaxies = getGalaxies(map);
   auto rows = emptyRows(map);
   auto cols = emptyCols(map);
   for(int i = 0; i < galaxies.size() - 1; i++){
      for(int j = i+1; j < galaxies.size(); j++){
         auto g1 = galaxies[i];
         auto g2 = galaxies[j];
         long long dist = manhattan(g1,g2);
         long long emptyRowCol = numberOfEmptyRowsAndCols(rows,cols,g1,g2);
         // We need to subtract so we dont count it twice
         res += dist + emptyRowCol*expansion - emptyRowCol;
      }
   }
   return res;
}

int main(){

   auto map = parse();
   auto resP1 = solve(map, 2);
   auto resP2 = solve(map, 1000000);
   cout << "PartOne: " << resP1 << endl;
   cout << "PartTwo: " << resP2 << endl;
}
