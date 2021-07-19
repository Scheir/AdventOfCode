#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <regex>

using namespace std;

int main(){
    regex re("([0-9]+): ([0-9]+)");
    smatch m;
    string str;
    vector<pair<int, int>> vp;
    int max = 0;
    while(getline(cin, str)){
        regex_match(str, m, re);
        int first = stoi(m[1]);
        int second = stoi(m[2]);
        max = first > max ? first : max;
        vp.push_back({first, second});
    }

    int res = 0;
    for(int i = 0; i <= max; i++){
        for(auto x : vp){
            if(i == x.first){
                int zeroLoop = (x.second-1) * 2;
                if((i % (zeroLoop)) == 0){
                    res += i * x.second;
                }
            }
        }
    }

    cout << "PartOne: " << res << endl;

    //PartTwo
    //Solution is pretty slow, could probably use chinese reminder theorem here
    //for better perfomance.
    bool done = false;
    int idx = 0;
    while(!done){    
        res = 0;
        idx++;
        for(int i = idx; i <= max+idx; i++){
            for(auto x : vp){
                if((i-idx) == x.first){
                    int zeroLoop = (x.second-1) * 2;
                    if((i % (zeroLoop)) == 0){
                        res += i * x.second;
                    }
                }
            }
        }
        if(res == 0){
            done = true;
        }
    }

