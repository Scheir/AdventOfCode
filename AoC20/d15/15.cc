#include <map>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

using namespace std;

int main(){
    string str;
    map<int,pair<int,int>> m;
    int idx = 0;
    int lastSpoken = 0;
    int spoken = 0;
    while(getline(cin, str, ',')){
        idx++;
        m[stoi(str)] = make_pair(0,idx);
        lastSpoken = stoi(str);
    }

    int tmpIdx = idx;
    int tempLast = lastSpoken;
    map<int,pair<int,int>> tm = m;
    for(auto x : {2020, 30000000}){
        idx = tmpIdx;
        lastSpoken = tempLast;
        spoken = 0;
        m = tm;
        auto it = m.end();
        while(idx != x){
            idx++;
            if(it == m.end()){
                m[lastSpoken].first = 0;
                m[lastSpoken].second = idx-1;
                spoken = 0;
                m[spoken].first = m[spoken].second;
                m[spoken].second = idx;
                it = m.find(spoken);
            }
            else{
                spoken = m[lastSpoken].second - m[lastSpoken].first;
                it = m.find(spoken);
                m[spoken].first = m[spoken].second;
                m[spoken].second = idx;
            }
            
            lastSpoken = spoken;
        }
        if(x == 2020)
            cout << "PartOne: " << lastSpoken << endl;
        else
            cout << "PartTwo: " << lastSpoken << endl;
    }
}

