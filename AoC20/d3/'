#include <iostream> 
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

int main(){
    vector<string> v;
    string str;
    while(getline(cin, str)){
        v.push_back(str);
    }
   
    vector<pair<int,int>> vp;
    vp.push_back({1,1});
    vp.push_back({3,1});
    vp.push_back({5,1});
    vp.push_back({7,1});
    vp.push_back({1,2});
    vector<int> sums;
    for(auto x: vp){
        int sum = 0;
        int y = 0;
        for(int i = 0; i < v.size(); i+=x.second){
            int j = y % v[0].size();
            if(v[i][j] == '#'){
                sum++;
            }
            y += x.first;
        }
        sums.push_back(sum);
    }
    
    for(auto x : v)
        cout << x << endl;

    cout << "PartOne: " << sums[1] << endl;

    long res = 1;
    for(auto x : sums)
        res *= x;
    cout << "PartTwo: " << res << endl;

}
