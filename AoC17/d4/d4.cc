#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

int main(){

    string str;
    int res = 0;
    int res2 = 0;
    while(getline(cin, str)){
        stringstream ss(str);
        vector<string> tv;
        string ts = "";
        while(getline(ss, ts, ' ')){
            tv.push_back(ts);
        }
       
        //Part one 
        set<string> s(tv.begin(), tv.end());
        if(s.size() == tv.size()){
            res++;
        }

        //PartTwo
        s.clear();
        for(auto& x : tv){
            sort(x.begin(), x.end());
        }

        s = set<string>(tv.begin(), tv.end());
        if(s.size() == tv.size()){
            res2++;
        }
    }

    cout << "PartOne: " << res << endl;
    cout << "PartTwo: " << res2 << endl;
}

