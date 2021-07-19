#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <regex>

using namespace std;

int getDistance(int x, int y, int z){
    int yabs = abs(y);
    int zabs = abs(z);
    int res = 0;
    if(yabs > zabs){
        if(y > 0){
            res = yabs + x;
        }
        else{
            res = yabs - x;
        }
    }
    else{
        if(z > 0){
            res = zabs - x;
        }
        else{
            res = zabs + x;
        }
    }
    return res;
}

int main(){
    string str;
    vector<string> vec;
    getline(cin, str);

    regex re("([a-z]+)");
    smatch m;
    while(regex_search(str, m, re)){
        vec.push_back(m[1]);
        str = m.suffix();
    }

    int x = 0;
    int y = 0;
    int z = 0;

    int max = 0;

    for(auto d : vec){
        if(d == "n"){
            x++;
        }
        else if(d == "ne"){
            y++;
        }
        else if(d == "se"){
            z++;
        }
        else if(d == "s"){
            x--;
        }
        else if(d == "sw"){
            y--;
        }
        else if(d == "nw"){
            z--;
        }

        max = getDistance(x,y,z) > max ? getDistance(x,y,z) : max;
    }

    cout << "PartOne: " << getDistance(x,y,z) << endl;
    cout << "PartTwo: " << max << endl;

}
