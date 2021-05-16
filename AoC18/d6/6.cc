#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <map>

using namespace std;

int main(){
    string str;
    vector<pair<int,int>> vec;

    while(getline(cin, str)){
        int x = stoi(str.substr(0, str.find(",")));
        int y = stoi(str.substr(str.find(",")+1));
        vec.push_back({x,y});
    }

    map<int,int> m;
    for(int i = 0; i < vec.size(); i++)
        m[i] = 0;
    for(int i = 0; i < 4000; i++){
        for(int j = 0; j < 4000; j++){ 
            long winner = 10e9;
            int winnerIdx = 0;
            bool bequal = false;
            for(int x = 0; x < vec.size(); x++){
                int distance = abs(vec[x].second - i) + abs(vec[x].first - j);
                if(distance == winner){
                    bequal = true;
                }
                if(distance < winner){
                    winner = distance;
                    winnerIdx = x;
                    bequal = false;
                }
            }
            if(bequal){
                cout << "E"; 
                continue;
            }
            m[winnerIdx]++;
            cout << winnerIdx;  
        }
        cout << endl;
    }
                
    int res = 0;
    for(int i = 0; i <vec.size(); i++){
        if(vec[i].first != bigx && vec[i].first != smallx && vec[i].second != bigy && vec[i].second != smally){
            res = res > m[i] ? res : m[i];
            cout << res << endl;
        }
    }
    
    cout << "PartOne: " << res << endl;
}

