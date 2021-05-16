#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <queue>
#include <tuple>
#include <stack>

using namespace std;

constexpr int yMAX = 14;


int main(){
    string str;
    vector<vector<char>> mat(2000,vector<char>(2000, '.'));
    int ymax = 0;
    int ymin = 100000;
    int xmax = 0;
    int xmin = 100000;
    while(getline(cin, str)){
       int comma = str.find(",");
       int secEqual = str.rfind("=");
       int firstDot = str.find(".");
       int lastDot = str.rfind("."); 
       int first = stoi(str.substr(2, comma-1));
       int second = stoi(str.substr(secEqual+1, firstDot-1));
       int third = stoi(str.substr(lastDot+1));

       if(str[0] == 'x'){
           for(int y = second; y <= third; y++)
           {
               mat[y][first] = '#';
               xmax = max(first, xmax);
               xmin = min(first, xmin);
               ymax = max(third, ymax);
               ymin = min(second, ymin);
           }
       }
       else{
           for(int x = second; x < third; x++){
               mat[first][x] = '#';
               xmax = max(third, xmax);
               xmin = min(second, xmin);
               ymax = max(first, ymax);
               ymin = min(first, ymin);
           }
       }
    }
    
    stack<tuple<int, int, char>> q;
    q.push(make_tuple(1, 500, '|'));
    xmax = xmax + 10;
    xmin = xmin - 10;

    while(!q.empty()){
        int x;
        int y;
        char c;
        tie(y,x,c) = q.top();
        q.pop();
        mat[y][x] = c; 
        if((c == '|' || c == '/' ) && y <= ymax)
        {
            if(mat[y+1][x] == '.'){
                for(int i = y+1; i <= ymax; i++){
                    if(mat[i][x] == '#' || mat[i][x] == '|' ){
                        break;
                    }
                    q.push(make_tuple(i,x,'|'));
                }
            }
            else if((mat[y+1][x] == '~' || mat[y+1][x] == '#') && c != '/'){
                int xleft = xmin;
                int xright = xmax;
                for(int i = x; i >= xmin; i--){
                    if(mat[y][i] == '#'){
                        xleft = i;
                        break;
                    }
                }
                for(int i = x+1; i <= xmax; i++){
                    if(mat[y][i] == '#'){
                        xright = i;
                        break;
                    }
                }
                bool isUpperBoundary = false;
                
                for(int i = x; i < xright; i++){
                    if(mat[y+1][i] == '.' || mat[y+1][i] == '|' || mat[y][x] == '#')
                    {
                        isUpperBoundary = true;
                        xright = i;
                        break;
                    }
                }
                for(int i = x-1; i > xleft; i--){
                    if(mat[y+1][i] == '.' || mat[y+1][i] == '|' || mat[y][x] == '#'){
                        isUpperBoundary = true;
                        xleft = i;
                        break;
                    }
                }
                if(isUpperBoundary){
                    for(int i = x; i >= xleft; i--){
                        if(mat[y][i] != '~'){
                            q.push(make_tuple(y,i,'/'));
                        }
                        if(mat[y+1][i] == '.' || mat[y][i-1] == '#')
                            break;
                    }
               
                    for(int i = x; i <= xright; i++){
                        if(mat[y][i] != '~')
                            q.push(make_tuple(y,i,'/'));
                        if(mat[y+1][i] == '.' || mat[y][i+1] == '#'){
                            break;
                        }
                    }
                }
                else{
                    q.push(make_tuple(y-1, x, '|'));
                    for(int i = xleft+1; i < xright; i++){
                        q.push(make_tuple(y,i,'~'));
                    }
                } 
            }
        }
    }

    for(int i = ymin; i < ymax; i++){
        for(int j = xmin; j < xmax; j++){
            char ch = mat[i][j];
            if(ch == '|' || ch == '/'){
                if(mat[i][j-1] =='~' || mat[i][j+1] == '~'){
                    mat[i][j] = '~';
                }
            }
        }
    }

    for(int i = ymin; i <= ymax; i++){
        for(int j = xmin; j <= xmax+1; j++){
           cout <<  mat[i][j];
        }
        cout << endl;
    }
    cout << endl;
    int counter = 0;
    int counter2 = 0;
    for(int i = ymin; i <= ymax; i++){
        for(int j = xmin; j < xmax; j++){
            char ch = mat[i][j];
            if(ch == '~' || ch == '|' || ch == '/')
                counter++;
            if(ch == '~')
                counter2++;
        }
    }
    cout << "PartOne: " << counter << endl;
    cout << "PartTwo: " << counter2 << endl;
}
    
