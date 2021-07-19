#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector<int> solve(vector<int> in, int rounds){
    
    vector<int> vec(256);
    iota(vec.begin(), vec.end(), 0);
    int skip = 0;
    int size = vec.size();
    int pointer = 0;
    for(int i = 0; i < rounds; i++){
        for(auto x : in){
            vector<int> temp;
            for(int i = pointer; i < pointer + x; i++){
                int idx = i % size;
                temp.push_back(vec[idx]);
            }

            reverse(temp.begin(), temp.end());
            for(int i = pointer, j = 0; i < x+pointer; i++, j++){
                int idx = i%size;
                vec[idx] = temp[j];
            }
            
            pointer += (x + skip);
            skip++;
        }
    }

    return vec;
}

int main(){
    string str;
    vector<int> in;
    getline(cin, str);
    stringstream ss(str);
    string temp;
    while(getline(ss, temp, ',')){
        in.push_back(stoi(temp));
    }

    auto vec = solve(in, 1);
    cout << "PartOne: " << vec.front() * vec[1] << endl;

    vector<int> in2;
    for(auto c : str){
        in2.push_back(static_cast<int>(c));
    }

    vector<int> extra({17, 31, 73, 47, 23});
    for(auto x : extra){
        in2.push_back(x);
    }

    auto vec2 = solve(in2, 64);

    vector<int> denseHash;
    for(int i = 0; i < 16; i++){
        int temp = vec2[i*16];
        for(int j = 1; j < 16; j++){
            int idx = i*16+j;
            temp ^= vec2[idx];
        }
        denseHash.push_back(temp);
    }

    string res;
    for(auto x : denseHash){
        stringstream ss;
        ss << hex << setw(2) << setfill('0') << x;
        res += ss.str();
    }

    cout << "PartTwo: " << res << endl;
}

