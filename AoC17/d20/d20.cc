#include <iostream>
#include <vector>
#include <tuple>
#include <regex>
#include <string>

using namespace std;

int main(){
    vector<tuple<vector<int>, vector<int>, vector<int>>> vec;

    string str;
    regex re("(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)");
    smatch m;
    while(getline(cin, str)){
        int px, py, pz, vx, vy, vz, ax, ay, az;
        regex_search(str, m, re);
        px = stoi(m[1]);
        py = stoi(m[2]);
        pz = stoi(m[3]);
        str = m.suffix();

        regex_search(str, m, re);
        vx = stoi(m[1]);
        vy = stoi(m[2]);
        vz = stoi(m[3]);
        str = m.suffix();

        regex_search(str, m, re);
        ax = stoi(m[1]);
        ay = stoi(m[2]);
        az = stoi(m[3]);
        
        vector<int> p = {px,py,pz};
        vector<int> v = {vx,vy,vz};
        vector<int> a = {ax,ay,az};

        vec.push_back({p,v,a});
    }

    for(int i = 0; i < 10000; i++){
        for(auto& x : vec){
            vector<int> pt(3,0);
            vector<int> vt(3,0);
            vector<int>& p = get<0>(x);
            vector<int>& v = get<1>(x);
            // a is not changing... no ref needed.
            vector<int> a = get<2>(x);
            
            for(int j = 0; j < 3; j++){
                vt[j] = v[j] + a[j];
                pt[j] = p[j] + v[j];
            }
            p = pt;
            v = vt;
        }
        for(auto& x: vec){
            auto p = get<0>(x);
            int count = count_if(vec.begin(), vec.end(), [p](tuple<vector<int>, vector<int>, vector<int>> t){
                auto pp = get<0>(t);
                int match = 0;
                for(int i = 0; i < 3; i++){
                    if(p[i] == pp[i]){
                        match++;
                    }
                }
                return match == 3;
            });
            if(count > 1){
                vec.erase(remove_if(vec.begin(), vec.end(), [p](tuple<vector<int>, vector<int>, vector<int>> t){
                    int count = 0;
                    auto pp = get<0>(t);
                    for(int i = 0; i < 3; i++){
                        if(p[i] == pp[i]){
                            count++;
                        }
                    }
                    return count == 3;
                }), vec.end());
            }
        }
    }

    long long min = numeric_limits<long long>::max();
    int idx = 0;
    int winner = 0;
    for(auto x : vec){
        auto p = get<0>(x);
        long long dist = abs(p.front()) + abs(p[1]) + abs(p.back());
        if(min > dist){
            min = dist;
            winner = idx;
        }
        idx++;
    }

    cout << "PartOne: " << winner << endl;
    cout << "PartTwo: " << vec.size() << endl;
            
        
}
