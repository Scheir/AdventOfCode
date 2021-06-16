#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

constexpr int PREAMBLES = 25;

int main(){
    long num;
    vector<long> vec;
    while(cin >> num){
        vec.push_back(num);
    }

    bool found = false;
    long winner = 0;
    for(int i = PREAMBLES; i < vec.size() || !found; i++){
        found = false;
        for(int j = i - PREAMBLES; j < i; j++){
            for(int l = i - PREAMBLES; l < i; l++){
                if(j == l)
                    continue;
                if(vec[l] + vec[j] == vec[i])
                {
                    found = true;
                }
            }
        }
        if(!found)
            winner = vec[i];
    }
    long winner2 = 0;
    long sum = 0;
    for(int i = 0; i < vec.size() && sum != winner; i++){
        sum = 0;
        int idx = i+1;
        vector<long> temp;
        while(sum < winner){
            sum += vec[idx]; 
            temp.push_back(vec[idx]);
            idx++;
        }
        if(sum == winner){
            sort(temp.begin(), temp.end());
            winner2 = temp.front() + temp.back();
        }
    }
    cout << "PartOne: " << winner << endl;
    cout << "PartTwo: " << winner2 << endl;
}

