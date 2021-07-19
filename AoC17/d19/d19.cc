#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    string str;
    vector<string> vec;
    while(getline(cin, str)){
        vec.push_back(str);
    }

    int x = 0;
    int y = vec[0].find("|");
    char dir = 'v';

    bool done = false;
    string res = "";
    int count = 0;
    while(!done){
        if(vec[x][y] == ' '){
            done = true;
            break;
        }
        count++;
        if(dir == 'v'){
            x++;
            if(vec[x][y] == '+'){
                if(vec[x][y-1] == ' '){
                    dir = '>';
                }
                else{
                    dir = '<';
                }
            }
            else if(isupper(vec[x][y])){
                res += vec[x][y];
            }
        }
        else if(dir == '^'){
            x--;
            if(vec[x][y] == '+'){
                if(vec[x][y-1] == ' '){
                    dir = '>';
                }
                else{
                    dir = '<';
                }
            }
            else if(isupper(vec[x][y])){
                res += vec[x][y];
            }
        }
        else if(dir == '>'){
            y++;
            if(vec[x][y] == '+'){
                if(vec[x-1][y] == ' '){
                    dir = 'v';
                }
                else{
                    dir = '^';
                }
            }
            else if(isupper(vec[x][y])){
                res += vec[x][y];
            }
        }
        else if(dir == '<'){
            y--;
            if(vec[x][y] == '+'){
                if(vec[x-1][y] == ' '){
                    dir = 'v';
                }
                else{
                    dir = '^';
                }
            }
            else if(isupper(vec[x][y])){
                res += vec[x][y];
            }
        }
    }

    cout << "PartOne: " << res << endl;
    cout << "PartTwo: " << count << endl;
                    
}

