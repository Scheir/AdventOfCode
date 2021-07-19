#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

int main(){
    int num;
    vector<int> vec;
    while(cin >> num)
        vec.push_back(num);

    bool done = false;
    map<string, int> m;
    int iterations = 0;
    int res1 = 0;
    string searchString = "";
    while(!done){
        auto it = max_element(vec.begin(), vec.end());
        int max = *it;
        int addPerMem = max/(vec.size()-1);
        if(addPerMem == 0)
            addPerMem = 1;
        for(auto iter = it; iter != vec.end() && (*it - addPerMem) >= 0; iter++){
            if(iter != it){
                *iter += addPerMem;
                *it -= addPerMem;
            }
        }

        for(auto iter = vec.begin(); iter != it && (*it - addPerMem) >= 0; iter++){
            if(iter != it){
                *iter += addPerMem;
                *it -= addPerMem;
            }
        }
        
        string str = "";
        for(auto x : vec){
            str += to_string(x) + ",";
        }
        
        if(m.find(str) != m.end()){
            res1 = iterations;
            searchString = str;
            done = true;
        }
        else{
            m[str] = iterations; 
        }
        iterations++;
    }

    cout << "PartOne: " << iterations << endl;

    // Difference between the two itterations where the same string happens
    // Have to subtract by one to get "Before" the same state again.
    cout << "PartTwo: " << iterations - m[searchString] - 1 << endl;

}
