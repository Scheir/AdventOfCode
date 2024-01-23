#include "../../aoc_tools.hpp"
#include <string>
#include <vector>
#include <optional>
#include <numeric>
#include <queue>

using namespace std;
queue<int> p1MirrorScore;

vector<vector<string>> parse(){
   auto lines = AOC::getLines();
   vector<vector<string>> ret;
   vector<string> temp;
   for(const auto& line : lines){
      if(line.size() == 0){
         ret.push_back(temp);
         temp.clear();
      }
      else{
         temp.push_back(line);
      }
   }
   if(temp.size()){
      ret.push_back(temp);
   }
   return ret;
}

// Unfortunatley p2 makes the code look like shit, but pass p1Val and p2 for
// simple sake.
optional<int> mirrorRow(const vector<string>& mirror, int p1Val = 0, bool col = false){
   for(int i = 0; i < mirror.size() - 1; i++){
      bool isMirror = true;
      for(int l = i, h = i+1; l >= 0 && h < mirror.size(); l--, h++){
         const auto& lowRow = mirror[l];
         const auto& highRow = mirror[h];
         if(lowRow != highRow){
            isMirror = false;
            break;
         }
      }
      // The second condition is for part two. It makes sure that we are not
      // returning the same result as in p1. Since the the new mirror doesnt necesarrily
      // break the old one, we need to keep iterate in case the old mirror shows up before
      // the new mirror.
      if(isMirror && p1Val != ((i+1)*(col ? 1 : 100))){
         return i+1;
      }
   }
   return {};
}

vector<string> transpose(const vector<string>& mirror){
   vector<string> transposed;
   for(int j = 0; j < mirror.front().size(); j++){
      string col;
      for(int i = 0; i < mirror.size(); i++){
         col.push_back(mirror[i][j]);
      }
      transposed.push_back(col);
   }
   return transposed;
}

int mirrorLambda(int left, const vector<string>& mirror){
   auto rowMirror = mirrorRow(mirror);
   auto right = rowMirror.has_value() ? rowMirror.value() * 100 : mirrorRow(transpose(mirror)).value();
   p1MirrorScore.push(right);
   return left + right;
}

int solvePartOne(const vector<vector<string>>& mirrors){
   return accumulate(mirrors.begin(), mirrors.end(), 0, mirrorLambda);
}

int partTwoMirrorLambda(int left, const vector<string>& mirror){
   auto curMirrorP1Score = p1MirrorScore.front();
   p1MirrorScore.pop();
   for(size_t i = 0; i < mirror.size(); i++){
      for(size_t j = 0; j < mirror.front().size(); j++){
         auto mirrorCpy = mirror;
         mirrorCpy[i][j] = mirrorCpy[i][j] == '.' ? '#' : '.';

         auto rowMirror = mirrorRow(mirrorCpy, curMirrorP1Score, false);
         if(rowMirror.has_value() && rowMirror.value()){
            return left + rowMirror.value() * 100;
         }

         auto colMirror = mirrorRow(transpose(mirrorCpy), curMirrorP1Score, true);
         if(colMirror.has_value() && colMirror.value()){
            return left + colMirror.value();
         }
      }
   }
   cerr << "Something went wrong" << endl;
   return 0;
}

int solvePartTwo(const vector<vector<string>>& mirrors){
   return accumulate(mirrors.begin(), mirrors.end(), 0, partTwoMirrorLambda);
}

int main(){
   auto mirrors = parse();
   auto resP1 = solvePartOne(mirrors);
   auto resP2 = solvePartTwo(mirrors);
   cout << "PartOne: " << resP1 << endl;
   cout << "PartTwo: " << resP2 << endl;
}
