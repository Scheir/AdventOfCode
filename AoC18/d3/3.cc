#include <iostream>
#include <vector>
#include <tuple>
#include <regex>

using namespace std;

int main(){

    regex re("([0-9]+)");
    smatch m;
    string str;
    vector<tuple<int,int,int,int,int>> vec;
    while(getline(cin , str)){
        vector<int> v;
        while(regex_search(str, m, re)){
            v.push_back(stoi(m[0]));
            str = m.suffix();
        }
        vec.push_back({v[0], v[1], v[2], v[3], v[4]});
    }

    vector<vector<int>> fab(1010, vector<int>(1010,0));


    for(auto& elem : vec){
        int id,x,y,dx,dy;
        tie(id,x,y,dx,dy) = elem;
        for(int i = y; i < dy+y; i++){
            for(int j = x; j < dx+x; j++){
                fab[i][j]++;
            }
        }
    }

    int res = 0;
    for(auto x : fab){
        for(auto xx : x){
            if(xx >= 2)
                res++;
        }
    }
    cout << "PartOne: " << res << endl;


    for(auto& elem : vec){
        int id,x,y,dx,dy;
        tie(id,x,y,dx,dy) = elem;
        bool finnished = true;
        for(int i = y; i < dy+y; i++){
            for(int j = x; j < dx+x; j++){
                if(fab[i][j] != 1){
                    finnished = false;
                }
            }
        }
        if(finnished){
            cout << "PartTwo: " << id << endl;
            exit(0);
        }
    }
}
