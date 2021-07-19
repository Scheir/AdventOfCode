#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <regex>
#include <map>

using namespace std;

int main(){
    regex re("([a-z]+) (inc|dec) (-?[0-9]+) if ([a-z]+) ([!=<>]+) (-?[0-9]+)");
    smatch ma;
    string str;
    map<string, int> m; 
    vector<tuple<string, string, int, string, string, int>> op;
    while(getline(cin, str)){
        regex_match(str, ma, re);
        m[ma[1]] = 0;
        op.push_back({ma[1], ma[2], stoi(ma[3]), ma[4], ma[5], stoi(ma[6])});
    }

    int res = 0;
    for(auto t : op){
        string toName;
        string incDec;
        int incDecVal;
        string ifName;
        string cond;
        int condVal;
        tie(toName, incDec, incDecVal, ifName, cond, condVal) = t;
        
        if(cond == "=="){
            if(m[ifName] == condVal){
                if(incDec == "inc"){
                    m[toName] += incDecVal;
                }
                else{
                    m[toName] -= incDecVal;
                }
            }
        }
        if(cond == "!="){
            if(m[ifName] != condVal){
                if(incDec == "inc"){
                    m[toName] += incDecVal;
                }
                else{
                    m[toName] -= incDecVal;
                }
            }
        }
        if(cond == ">"){
            if(m[ifName] > condVal){
                if(incDec == "inc"){
                    m[toName] += incDecVal;
                }
                else{
                    m[toName] -= incDecVal;
                }
            }
        }
        if(cond == ">="){
            if(m[ifName] >= condVal){
                if(incDec == "inc"){
                    m[toName] += incDecVal;
                }
                else{
                    m[toName] -= incDecVal;
                }
            }
        }
        if(cond == "<"){
            if(m[ifName] < condVal){
                if(incDec == "inc"){
                    m[toName] += incDecVal;
                }
                else{
                    m[toName] -= incDecVal;
                }
            }
        }
        
        if(cond == "<="){
            if(m[ifName] <= condVal){
                if(incDec == "inc"){
                    m[toName] += incDecVal;
                }
                else{
                    m[toName] -= incDecVal;
                }
            }
        }

        res = m[toName] > res ? m[toName] : res;
    }

    int max = 0;
    for(auto x : m)
        max = x.second > max ? x.second : max;

    cout << "PartOne: " << max << endl;
    cout << "PartTwo: " << res << endl;
}
