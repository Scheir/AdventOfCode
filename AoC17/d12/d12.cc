#include <iostream>
#include <vector>
#include <set>
#include <regex>
#include <utility>

using namespace std;

static set<int> s;
void solve(vector<pair<int, vector<int>>> vp, int searchInt){
    s.insert(searchInt);
    auto it = find_if(vp.begin(), vp.end(), [searchInt](pair<int, vector<int>> p){
        return searchInt == p.first;
    });

    auto matches = (*it).second;
    for(auto match : matches){
        if(s.find(match) == s.end()){
            solve(vp, match);
        }
    }
}
    


int main(){
    string str;
    vector<pair<int, vector<int>>>  vp;
    while(getline(cin, str)){
        regex re("([0-9]+)");
        smatch m;
        vector<int> tempVec;
        regex_search(str, m, re);
        int tempInt = stoi(m[1]);
        str = m.suffix();
        while(regex_search(str, m ,re)){
            int t = stoi(m[1]);
            tempVec.push_back(t);
            str = m.suffix();
        }
        vp.push_back({tempInt, tempVec});
    }

    solve(vp, 0);
    int res = s.size();
    cout << "PartOne: " << res << endl;

    int res2 = 1;
    for(auto x : vp){
        int cur = x.first;
        if(s.find(cur) == s.end()){
            res2++;
            solve(vp, cur);
        }
    }

    cout << "PartTwo: " << res2 << endl;
}


