#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int solve(vector<int> vec, int& idx)
{
    int sum = 0;
    int childs = vec[idx++];
    int metaEntries = vec[idx++];
    int limit = idx + childs;
    for(int i = idx; i < limit; i++){
        sum += solve(vec, idx);
    }
    limit = idx + metaEntries;
    for(int i = idx; i < limit; i++){
        sum += vec[idx++];
    }

    return sum;
} 

static map<string,int> m;
void solvePartTwo(vector<int> vec, int& idx, string mIdx){
    int childs = vec[idx++];
    int metaEntries = vec[idx++];
    int limit = idx + childs;
    int strIdx = 1;
    for(int i = idx; i < limit; i++){
        solvePartTwo(vec, idx, mIdx + to_string(strIdx)); 
        strIdx++;
    }

    limit = idx + metaEntries;
    m[mIdx] = 0;
    for(int i = idx; i < limit; i++){
        if(childs == 0){
            m[mIdx] += vec[idx++];
        }
        else{
            if(m.find(mIdx+to_string(vec[idx])) != m.end()){
                m[mIdx] += m[mIdx+to_string(vec[idx])];
            }
            idx++;
        }
    }
}

int main(){
    int num = 0;
    vector<int> vec;
    while(cin >> num){
        vec.push_back(num);
    }

    //PartOne
    int idx = 0;
    int res = solve(vec, idx);
    cout << "PartOne: " << res << endl;

    //PartTwo
    int idx2 = 0;
    string mIdx = "1";
    solvePartTwo(vec, idx2, mIdx);
    cout << "PartTwo: " << m["1"] << endl;
}
