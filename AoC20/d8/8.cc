#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <regex>
#include <set>
#include <algorithm>

using namespace std;

int main(){
    string str;
    vector<pair<string,int>> vec;
    while(getline(cin, str)){
        regex re("([a-z]{3}).*([+-][0-9]+)");
        smatch m;
        regex_match(str, m, re);
        vec.push_back({m[1], stoi(m[2])});
    }

    int idx = 0;
    bool firstRun = true;
    int idxnj = 0;
    int score = 0;
    while(idx != vec.size()){
        vector<pair<string,int>> tvec = vec;
        if(!firstRun){
            auto it = find_if(tvec.begin()+idxnj+1, tvec.end(), [](pair<string,int> a){
                return a.first == "jmp" || a.first == "nop";
                });
            it->first = it->first == "jmp" ? "nop" : "jmp";
            idxnj += distance(tvec.begin()+idxnj, it);
        }
        set<int> s;
        bool done = false;
        idx = 0;
        score = 0;
        while(!done){
            string tstr = tvec[idx].first;
            int tint = tvec[idx].second;
            if(tstr == "nop"){
                idx++;
            }
            else if(tstr == "acc"){
                score += tint;
                idx++;
            }
            else if(tstr == "jmp"){
                idx += tint;
            }

            if(s.find(idx) != s.end() || idx == vec.size())
                done = true;
            s.insert(idx);
        }
        if(firstRun){
            cout << "PartOne: " << score << endl;
            firstRun = false;
        }
    }
    cout << "PartTwo: " << score << endl;
}
