#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

struct worker{
    worker() {}
    int workTime = 0;
    string object = "NONE";
    bool isFree(){return workTime == 0;}
};
    
bool anyFreeWorkers(vector<worker>& v){
    for(auto& x : v)
        if(x.isFree())
            return true;
    return false; 
}

worker& getFreeWorker(vector<worker>& v){
    for(auto& x : v){
        if(x.isFree())
            return x;
    }
}

void decrementWorkTime(vector<worker>& v){
    for(auto& x : v)
        if(x.workTime != 0)
            x.workTime--;
}

int main(){
    string str;
    vector<pair<string,string>> vec;
    while(getline(cin, str)){
        vector<string> tv;
        string ts;
        stringstream ss(str);
        while(getline(ss, ts, ' '))
            if(ts.size() == 1)
                tv.push_back(ts);
        vec.push_back({tv[0], tv[1]});
    }
    
    map<string,vector<string>> m, m2;
    for(auto x: vec){
        if(m.find(x.second) == m.end())
            m.emplace(x.second, vector<string>());
        m[x.first].push_back(x.second);
        sort(m[x.first].begin(), m[x.first].end());
    }
   
    //m2 is needed for part 2.
    m2 = m;

    //PartOne
    string res = "";
    while(!m.empty()){
        for(auto& x : m){
            bool noDep = true;
            for(auto y : m){
                for(auto s : y.second){
                    if(s == x.first){
                        noDep = false;
                        break;
                    }
                }
                if(!noDep)
                    break;
            }
            if(noDep){
                res += x.first;
                m.erase(x.first);
                break;
            }
        }
    }

    cout << "PartOne: " << res << endl;

    //PartTwo
    vector<string> workedObjs;
    int workerCount = 5;
    vector<worker> workers;
    for(int i = 0; i < workerCount; i++){
        workers.push_back(worker());
    }

    int time = 0;
    for(; !m2.empty(); time++){
        for(auto &x : m2 ){
            bool noDep = true;
            for(auto y : m2){
                for(auto s : y.second){ 
                    if(x.first == s){
                        noDep = false;
                        break;
                    }
                }
                if(!noDep)
                    break;
            }
            if(noDep){
                bool objectNeedWork = find(workedObjs.begin(), workedObjs.end(), x.first) == workedObjs.end();
                if(anyFreeWorkers(workers) && objectNeedWork){
                    auto& w = getFreeWorker(workers);
                    w.workTime = 60 + (x.first[0] - '@');
                    w.object = x.first; 
                    workedObjs.push_back(x.first);
                }
            }
        }

        decrementWorkTime(workers);
        for(auto x : workers)
            if(x.isFree()){
                m2.erase(x.object);
            }
    }
    cout <<"PartTwo: " <<  time << endl;
}

