#include <iostream>
#include <utility>
#include <vector>
#include <regex>

using namespace std;

static int winner = 0;
static int winner2 = 0;
static int winnerLength = 0;

void solve(vector<pair<int,int>> vp, pair<int,int> p, int number, int sum, int length){
    length++;
    vp.erase(remove_if(vp.begin(), vp.end(), [p](pair<int,int> e){
        if(p.first == e.first && p.second == e.second){
            return true;
        }
        return false;
    }), vp.end());
    sum += (p.first + p.second);
    auto it = find_if(vp.begin(), vp.end(), [number](pair<int,int> e){
        return number == e.first || number == e.second;
    });
    if(it == vp.end()){
        if(length > winnerLength){
            winnerLength = length;
            winner2 = sum;
        }
        else if(length == winnerLength){
            winner2 = sum < winner2 ? winner2 : sum;
        }
        winner = sum < winner ? winner : sum;
    }
    else{
        for(auto x : vp){
            if(x.first == number){
                solve(vp, x, x.second, sum, length);
            }
            if(x.second == number){
                solve(vp, x, x.first, sum, length);
            }
        }
    }
}

        

int main(){
    string str;
    regex re("([0-9]+).([0-9]+)");
    smatch m;
    vector<pair<int,int>> vp;
    while(getline(cin, str)){
        regex_match(str, m, re);
        int a = stoi(m[1]);
        int b = stoi(m[2]);
        vp.push_back({a,b});
    }
    for(auto x : vp){
        auto vpc = vp;
        if(x.second == 0)
            solve(vpc, x, x.first, 0, 0);
        if(x.first == 0)
            solve(vpc, x, x.second, 0, 0);
    }
    cout << "PartOne: " << winner << endl;
    cout << "PartTwo: " << winner2 << endl;
}
