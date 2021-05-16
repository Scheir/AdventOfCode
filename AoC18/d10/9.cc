#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>
#include <unistd.h>

using namespace std;
//position=< 9,  1> velocity=< 0,  2>

int main(){
    string str;
    vector<pair<int,int>> vp, vv;
    while(getline(cin, str)){
        int arrow = str.find("<");
        int comma = str.find(",");
        int rArrow = str.find(">");
        string posx = str.substr(arrow+1, comma-arrow-1);
        string posy = str.substr(comma+1, rArrow-comma-1);
        int px = posx[0] == ' ' ? stoi(posx.substr(1)) : stoi(posx);
        int py = posy[0] == ' ' ? stoi(posy.substr(1)) : stoi(posy);
        arrow = str.find("<", arrow+1);
        comma = str.find(",", comma+1);
        rArrow = str.find(">", rArrow+1);
        string velx = str.substr(arrow+1, comma-arrow-1);
        string vely = str.substr(comma+1, rArrow-comma-1);
        int vx = velx[0] == ' ' ? stoi(velx.substr(1)) : stoi(velx);
        int vy = vely[0] == ' ' ? stoi(vely.substr(1)) : stoi(vely);
        vp.push_back({px, py});
        vv.push_back({vx, vy});
    }

    // Get rid of 4&5th digit.
    for(int i = 0; i < vp.size(); i++){
        vp[i].first += 10505*vv[i].first;
        vp[i].second += 10505*vv[i].second;
    } 

    vector<pair<int,int>> tv = vp;
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < tv.size(); j++){
            tv[j].first += vv[j].first;
            tv[j].second += vv[j].second;
        }
        for(int x = 0; x <= 200; x++){
            for(int y = 50; y <= 300; y++){
                if(find(tv.begin(), tv.end(), make_pair(y,x)) != tv.end())
                    cout << "#";
                else
                    cout << ".";
                usleep(20);
            }
            cout << endl;
        }
        vp = tv;
    }
}
