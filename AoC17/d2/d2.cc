#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <limits>

using namespace std;

int main(){
    vector<vector<int>> vec;
    string str;
    while(getline(cin, str)){
        regex re("[0-9]+");
        smatch m;
        vector<int> v;
        while(regex_search(str, m, re)){
            v.push_back(stoi(m[0]));
            str = m.suffix();
        }
        vec.push_back(v);
    }

    long long sum = 0;
    long long sumTwo = 0;
    for(auto v : vec){
        // PartOne
        int min = numeric_limits<int>::max(); 
        int max = 0;
        for(auto x : v){
            max = max > x ? max : x;
            min = min < x ? min : x;
        }
        sum += max - min;

        //PartTwo
        for(auto a : v){
            for(auto b : v){
                if(a == b)
                    continue;
                if((a % b) == 0 && a > b){
                    sumTwo += a/b; 
                }
            }
        }
    }


    cout << "PartOne: " << sum << endl;
    cout << "PartTwo: " << sumTwo << endl;
}
