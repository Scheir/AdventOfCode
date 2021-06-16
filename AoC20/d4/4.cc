#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <functional>

using namespace std;

bool byr(string str, int min, int max){
    regex re("([0-9]{4})");
    smatch m;
    if(regex_match(str, m, re)){
        int num = stoi(m[0]);
        if(num >= min && num <= max)
            return true;
        else
            return false;
    }
    return false;
}

bool hgt(string str){
    regex re("([0-9]+)(cm|in)");
    smatch m;
    if(regex_match(str, m, re)){
        int num = stoi(m[1]);
        string str = m[2];
        if(str == "cm" && num >= 150 && num <= 193){
            return true;
        }
        else if(str == "in" && num >= 59 && num <= 76){
            return true;
        }
        else
            return false;
    }
    return false;
}

bool hcl(string str){
    regex re("#([0-9]|[a-f]){6}");
    smatch m;
    if(regex_match(str, m, re))
        return true;
    else
        return false;
}

bool ecl(string str){
    regex re("(amb|blu|brn|gry|grn|hzl|oth)+");
    smatch m;
    if(regex_match(str, m, re) && m.size() == 2)
        return true;
    else
        return false;
}

bool pid(string str){
    regex re("([0-9]+)");
    smatch m;
    if(regex_match(str, m, re) && m[0].str().size() == 9)
        return true;
    else
        return false;
}

int main(){
    string str = "";
    vector<string> vec{"byr","iyr","eyr","hgt","hcl","ecl","pid"}, strVec{}; 
    map<string,std::function<bool(string)>> m;
    m["byr"] = bind(&byr,placeholders::_1, 1920, 2002);
    m["iyr"] = bind(&byr,placeholders::_1, 2010, 2020);
    m["eyr"] = bind(&byr,placeholders::_1, 2020, 2030);
    m["hgt"] = bind(&hgt,placeholders::_1);
    m["hcl"] = bind(&hcl,placeholders::_1);
    m["ecl"] = bind(&ecl,placeholders::_1);
    m["pid"] = bind(&pid,placeholders::_1);
    string temp;
    while(getline(cin, temp)){
        if(temp.size() > 0)
        {
            str = str + " " + temp;
        }
        else{
            strVec.push_back(str);
            str = "";
        }
    }

    int res = 0;
    int res2 = 0;
    for(auto& str : strVec){
        bool ok = true;
        bool ok2 = true;
        for(auto &x : m){
            if(str.find(x.first) != string::npos){
                int pos = str.find(x.first) + 4;
                int space = str.find(" ", pos);
                space = space == 0 ? 100 : space;
                string tstr = str.substr(pos, space-pos);
                if(!x.second(tstr)){
                    ok2 = false;
                    break;
                }
            }
            else{
                ok = false;
                ok2 = false;
                break;
            }
        }
        if(ok){
           res++;
        }
        if(ok2){
            res2++;
        }
    }
    
    cout << "PartOne: " << res << endl;
    cout << "PartTwo: " << res2 << endl;
}
