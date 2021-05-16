#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

using namespace std;


int main(){
    string str;
    int sum = 0;
    int p2 = 0;
    vector<int> sums, val;
    while(getline(cin,str)){
        sum += stoi(str);
        if((find(sums.begin(), sums.end(), sum) != sums.end()) && p2 == 0)
            p2 = sum;
        sums.push_back(sum);
        val.push_back(stoi(str));
    }
    cout << "PartOne: " << sum << endl;

    while(p2 == 0){
        for(auto x : val){
            sum += x;
            if(find(sums.begin(), sums.end(), sum) != sums.end()){
                p2 = sum;
                break;
            }
        }
    }
    cout << "PartTwo: " << p2 << endl;
}
