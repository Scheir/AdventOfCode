#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> vec;
    int num;
    while(cin >> num){
        vec.push_back(num);
    }
    //Vec for part two before breaking it
    vector<int> vec2 = vec;

    //Part one logic
    int n = vec.size();
    int cur = 0;
    int iterations = 0;
    while(cur < n){
        int temp = cur;
        cur += vec[cur];
        vec[temp]++;
        iterations++;
    }

    cout << "PartOne: " << iterations << endl;

    //Part Two
    cur = 0;
    iterations = 0;
    while(cur < n){
        int temp = cur;
        cur += vec2[cur];
        if(vec2[temp] >= 3){
            vec2[temp]--;
        }
        else{
            vec2[temp]++;
        }
        iterations++;
    }

    cout << "PartTwo: " << iterations << endl;

}
