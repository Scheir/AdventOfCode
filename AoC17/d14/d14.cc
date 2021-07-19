#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <bitset>

using namespace std;


void fillArea(vector<string>& vec, int x, int y){
    vec[x][y] = '#';
    if(vec[x+1][y] == 'X')
        fillArea(vec,x+1,y);
    if(vec[x-1][y] == 'X')
        fillArea(vec, x-1,y);
    if(vec[x][y+1] == 'X')
        fillArea(vec, x, y+1);
    if(vec[x][y-1] == 'X')
        fillArea(vec, x, y-1);
}

vector<int> solve(vector<int> in, int rounds){
    
    vector<int> vec(256);
    vector<int> extra = {17, 31, 73, 47, 23};
    for(auto x  : extra){
        in.push_back(x);
    }
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
    string str = "oundnydw";
    vector<string> hashes;

    for(int i = 0; i <= 127; i++){
        string s = str + "-" + to_string(i);
        hashes.push_back(s);
    }
    
    // Create input vector to solve function
    vector<vector<int>> intHashes;
    for(auto x : hashes){
        vector<int> t;
        for(auto c : x){
            t.push_back(static_cast<int>(c));
        }
        intHashes.push_back(t);
    }

    
    vector<string> knotHashes;
    for(auto x : intHashes){
        auto vec = solve(x, 64);
        vector<int> denseHash;
        for(int i = 0; i < 16; i++){
            int temp = vec[i*16];
            for(int j = 1; j < 16; j++){
                int idx = i*16+j;
                temp ^= vec[idx];
            }
            denseHash.push_back(temp);
        }

        string res;
        for(auto x : denseHash){
            stringstream ss;
            ss << hex << setw(2) << setfill('0') << x;
            res += ss.str();
        }
        knotHashes.push_back(res);
    } 

    vector<string> binalStrings;
    for(auto k : knotHashes){
        string binalString = "";
        for(auto c : k){
            string ts; 
            ts.push_back(c);
            stringstream ss;
            ss << bitset<4>(stoi(ts,nullptr,16));
            binalString += ss.str();
        }
        binalStrings.push_back(binalString);
    }

    int res = 0;
    for(auto& x : binalStrings){
        for(auto& c : x){
            if(c == '1'){
                res++;
                c = 'X';
            }
            else{
                c = ' ';
            }
        }
    }
                
    cout << "PartOne: " << res << endl;

    string edge = "";
    for(int i = 0; i < 130; i++)
        edge+= " ";

    vector<string> vec;
    vec.push_back(edge);
    for(auto x : binalStrings){
        string t  = " " + x + " ";
        vec.push_back(t);
    }
    vec.push_back(edge);
    
    int counter = 0;
    for(int i = 1; i < vec.size()-1; i++){
        for(int j = 1; j < vec[i].size(); j++){
            if(vec[i][j] == 'X'){
                fillArea(vec, i, j);
                counter++;
            }
        }
    }
    
    cout << "PartTwo: " << counter << endl;
}

