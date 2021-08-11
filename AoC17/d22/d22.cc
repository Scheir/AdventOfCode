#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct virus{
    int x;
    int y;
    char dir;
    virus(vector<string> v){
        int n = v.size();
        int idx = (n - 1) / 2;
        x = idx;
        y = idx;
        char c = v[idx][idx];
    }
    void move(){
        if(dir == '>'){
            y++;
        }
        else if(dir == '<'){
            y--;
        }
        else if(dir == '^'){
            x--;
        }
        else if(dir == 'v'){
            x++;
        }
    }
    void turn(char c){
        if(c == '.'){
            if(dir == '>'){
                dir = '^';
            }
            else if(dir == '^'){
                dir = '<';
            }
            else if(dir == '<'){
                dir = 'v';
            }
            else if(dir == 'v'){
                dir = '>';
            }
            else{
                dir = '<';
            }
        }
        else if(c == '#'){
            if(dir == '>'){
                dir = 'v';
            }
            else if(dir == 'v'){
                dir = '<';
            }
            else if(dir == '<'){
                dir = '^';
            }
            else if(dir == '^'){
                dir = '>';
            }
            else{
                dir = '>';
            }
        }
        else if(c == 'F'){
            if(dir == '>'){
                dir = '<';
            }
            else if(dir == '^'){
                dir = 'v';
            }
            else if(dir == '<'){
                dir = '>';
            }
            else if(dir == 'v'){
                dir = '^';
            }
        }
        else if(c == 'W'){
            // Nothing happens
        }
    }
};

int main(){
    vector<string> vec;
    vector<string> temp;
    string str;
    while(getline(cin, str)){
        temp.push_back(str);
    }

    int n = temp.size();
    int gridSize = n % 2 == 0 ? 800 : 801;
    int fill = gridSize - n;
    string s;
    string sadd;
    for(int i = 0; i < gridSize; i++){
        s += '.';
    }
    for(int i = 0; i < fill/2; i++){
        sadd += '.';
    }
    for(int i = 0; i < fill/2; i++){
        vec.push_back(s);
    }

    for(int i = 0; i < n; i++){
        string ts = sadd + temp[i] + sadd;
        vec.push_back(ts);
    }

    for(int i = 0; i < fill/2; i++){
        vec.push_back(s);
    }
    
    virus v(vec);
    auto vec2 = vec;
    // PartOne
    int res = 0;
    for(int i = 0; i < 10000; i++){
        int x = v.x;
        int y = v.y;
        if(vec[x][y] == '.'){
            vec[x][y] = '#';
            v.turn('.');
            res++;
        }
        else{
            vec[x][y] = '.';
            v.turn('#');
        }
        v.move();
    }
    cout << "PartOne: " << res << endl;
    
    //PartTwo
    virus v2(vec2);
    int res2 = 0;
    for(int i = 0; i < 10000000; i++){
        int x = v2.x;
        int y = v2.y;
        if(vec2[x][y] == '.'){
            vec2[x][y] = 'W';
            v2.turn('.');
            res++;
        }
        else if(vec2[x][y] == 'W'){
            vec2[x][y] = '#';
            v2.turn('W');
            res2++;
        }
        else if(vec2[x][y] == 'F'){
            vec2[x][y] = '.';
            v2.turn('F');
        }
        else{
            vec2[x][y] = 'F';
            v2.turn('#');
        }

        v2.move();
    }
    cout << "PartTwo: " << res2 << endl;
}
