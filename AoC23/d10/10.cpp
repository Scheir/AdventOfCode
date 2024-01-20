#include "../../aoc_tools.hpp"
#include <vector>
#include <map>
#include <functional>
#include <set>

using namespace std;

set<pair<size_t,size_t>> mazeBorder;

vector<string> parse(){
   return AOC::getLines();
}

char north(char next){
   if(next == '7')
      return '<';
   else if(next == 'F')
      return '>';
   else if(next == '|')
      return '^';
   else{
      cerr << "Error when walking north for char: " << next << endl;
      exit(1);
   }
}

char east(char next){
   if(next == '7')
      return 'v';
   else if(next == 'J')
      return '^';
   else if(next == '-')
      return '>';
   else{
      cerr << "Error when walking east for char: " << next << endl;
      exit(1);
   }
}

char south(char next){
   if(next == 'J')
      return '<';
   else if(next == 'L')
      return '>';
   else if(next == '|')
      return 'v';
   else{
      cerr << "Error when walking south for char: " << next << endl;
      exit(1);
   }
}

char west(char next){
   if(next == 'L')
      return '^';
   else if(next == 'F')
      return 'v';
   else if(next == '-')
      return '<';
   else{
      cerr << "Error when walking west for char: " << next << endl;
      exit(1);
   }
}

map<char,function<char(char)>> movement{
      {'v', south},
      {'<', west},
      {'^', north},
      {'>', east}
};

map<char,pair<int,int>> step{
   {'^', {-1,0}},
   {'>', {0,1}},
   {'v', {1,0}},
   {'<', {0,-1}}
};

pair<int,int> findS(const vector<string>& maze){
   for(size_t i = 0; i < maze.size(); i++){
      for(size_t j = 0; j < maze.front().size(); j++){
         const char& cur = maze[i][j];
         if(cur == 'S'){
            return {i,j};
         }
      }
   }
   cerr << "Did not find S " << endl;
   exit(1);
}

int moveTheMaze(int x, int y, const vector<string>& maze){
const auto endX {x};
const auto endY {y};
   // TODO: Find the start dir
   char dir = '>';
   int steps = 0;
   while(true){
      mazeBorder.insert({x,y});
      steps++;
      auto [dx,dy] = step[dir];
      x += dx;
      y += dy;
      if(x == endX & y == endY){
         break;
      }
      dir = movement[dir](maze[x][y]);
   }
   return steps & 1 ? steps / 2 + 1 : steps / 2;
}

int solvePartOne(const vector<string>& maze){
   auto [x, y] = findS(maze);
   return moveTheMaze(x,y,maze);
}

bool checkIfInside(size_t x, size_t y, const vector<string>& maze){
   string chars = "|LJ";
   size_t cnt = 0;
   for(size_t i = 0; i < y; i++){
      if(mazeBorder.find({x,i}) != mazeBorder.end()){
         cnt += chars.find(maze[x][i]) != string::npos ? 1 : 0;
      }
   }
   return cnt % 2 == 1;
}

size_t solvePartTwo(const vector<string>& maze){
   size_t res = 0;
   for(size_t i = 0; i < maze.size(); i++){
      for(size_t j = 0; j < maze.front().size(); j++){
         if(mazeBorder.find({i,j}) == mazeBorder.end()){
            if(checkIfInside(i,j,maze)){
               res++;
            }
         }
      }
   }
   return res;
}

int main(){
   const auto maze = parse();
   auto p1Res = solvePartOne(maze);
   auto p2Res = solvePartTwo(maze);
   cout << p1Res << endl;
   cout << p2Res << endl;

}

