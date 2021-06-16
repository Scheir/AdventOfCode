#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    string str;
    vector<string> vec;
    while(getline(cin, str)){
        vec.push_back("+"+str+"+");
    }

    str = "";
    for(int i = 0; i < vec.front().size(); i++)
        str += "+";
    
    vec.insert(vec.begin(), str);
    vec.push_back(str);
    
    vector<int> dx = {-1,0,1};
    vector<int> dy = {-1,0,1};
    vector<string> tempVec = vec;

    //For part two
    vector<string> v = vec;
    vector<string> tv = v;
    
    int done = 1;
    while(done != 0){
        done = 0;
        for(int i = 1; i < vec.size()-1; i++){
            for(int j = 1; j < vec.front().size()-1; j++){
                int count = 0;
                for(auto x : dx){
                    for(auto y : dy){
                        if(x == 0 && y == 0){
                            continue;
                        }
                        if(vec[i+x][j+y] == '#'){
                            count++;
                        }
                    }
                }
                if(vec[i][j] == '#' && count >= 4){
                    tempVec[i][j] = 'L';
                    done++;
                }
                else if(vec[i][j] == 'L' && count == 0){
                   tempVec[i][j] = '#';
                   done++;
                }
            }
        }
        vec = tempVec;
    }
    int res = 0;
    for(auto x : vec)
        for(auto xx : x)
            res = xx == '#' ? res + 1 : res;

    cout << "PartOne: " << res << endl;
    done = 1;

    while(done != 0)
    {
        done = 0;
        for(int i = 1; i < v.size() - 1; i++){
            for(int j = 1; j < v.front().size() - 1; j++){
                int c = 0;
                for(int y = j-1; y >= 0; y--){
                    if(v[i][y] == 'L')
                        break;
                    if(v[i][y] == '#'){
                        c++;
                        break;
                    }
                }
                for(int y = j+1; y < v.front().size(); y++){
                    if(v[i][y] == 'L')
                        break;
                    if(v[i][y] == '#'){
                        c++;
                        break;
                    }
                }
                for(int x = i-1; x >= 0; x--){
                    if(v[x][j] == 'L')
                        break;
                    if(v[x][j] == '#'){
                        c++;
                        break;
                    }
                }
                for(int x = i+1; x < v.size(); x++){
                    if(v[x][j] == 'L')
                        break;
                    if(v[x][j] == '#'){
                        c++;
                        break;
                    }
                }
                for(int x = i+1, y = j+1; x < v.size() && y < v.front().size(); x++, y++){
                    if(v[x][y] == 'L')
                        break;
                    if(v[x][y] == '#'){
                        c++;
                        break;
                    }
                }
                for(int x = i-1, y = j-1; x >= 0 && y >= 0; x--, y--){
                    if(v[x][y] == 'L')
                        break;
                    if(v[x][y] == '#'){
                        c++;
                        break;
                    }
                }
                for(int x = i+1, y = j-1; x < v.size() && y >= 0; x++, y--){
                    if(v[x][y] == 'L')
                        break;
                    if(v[x][y] == '#'){
                        c++;
                        break;
                    }
                }
                for(int x = i-1, y = j+1; x >= 0 && y < v.front().size(); x--, y++){
                    if(v[x][y] == 'L')
                        break;
                    if(v[x][y] == '#'){
                        c++;
                        break; 
                    }
                }
                if(v[i][j] == '#' && c >= 5){
                    tv[i][j] = 'L';
                    done++;
                }
                else if(v[i][j] == 'L' && c == 0){
                    tv[i][j] = '#';
                    done++;
                }
            }
        }
        v = tv;
    }
    
    int res2 = 0;
    for(auto x : tv)
        for(auto xx : x)
            res2 = xx == '#' ? res2 + 1 : res2;

    cout << "PartTwo: " << res2 << endl;

}
