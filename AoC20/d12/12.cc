#include <iostream>
#include <vector>
#include <regex>
#include <utility>
#include <string>

using namespace std;

int main(){
    string str;
    vector<pair<char,int>> vec;
    regex re("([A-Z])([0-9]+)");
    smatch m;
    while(getline(cin, str)){
        bool match = regex_match(str, m, re);
        char c = m[1].str()[0];
        int num = stoi(m[2].str());
        vec.push_back({c, num});
    }
    
    int x = 0; int y = 0; int dir = 90;
    
    for(auto p : vec){
        dir = dir % 360;
        char c = p.first;
        int num = p.second;
        if(c == 'N')
            y += num;
        else if(c == 'S')
            y -= num;
        else if(c == 'E')
            x += num;
        else if(c == 'W')
            x -= num;
        else if(c == 'L')
            dir -= num;
        else if(c == 'R')
            dir += num;
        else if(c == 'F'){
            if(dir == 90 || dir == -270)
                x += num;
            if(dir == 180 || dir == -180)
                y -= num;
            if(dir == 270 || dir == -90)
                x -= num;
            if(dir == 0)
                y += num;
        }
    } 
    cout << "PartOne: " << abs(x) + abs(y) << endl;
    
    int wpx = 10;
    int wpy = 1;
    int posx = 0;
    int posy = 0;
    dir = 0;
    for(auto p : vec){
        dir = dir % 360;
        char c = p.first;
        int num = p.second;
        if(c == 'N'){
            wpy += num;
        }
        if(c == 'E'){
            wpx += num;
        }
        if(c == 'S'){
            wpy -= num;
        }
        if(c == 'W'){
            wpx -= num;
        }
        if(c == 'R'){
            int ty = wpy;
            int tx = wpx;
            if(num == 90 || num == -270){
                wpy = -tx;
                wpx = ty;
            }
            if(num == 180 || num == -180){
                wpy = -ty;
                wpx = -tx;
            }
            if(num == 270 || num == -90){
                wpy = tx;
                wpx = -ty;
            }
        }
        if(c == 'L'){
            int ty = wpy;
            int tx = wpx;
            if(num == 270 || num == -90){
                wpy = -tx;
                wpx = ty;
            }
            if(num == 180 || num == -180){
                wpy = -ty;
                wpx = -tx;
            }
            if(num == 90 || num == -270){
                wpy = tx;
                wpx = -ty;
            }
        }
                
        if(c == 'F'){
            posx += num*wpx;
            posy += num*wpy;
        }
    }
    cout << "PartTwo: " << abs(posx) + abs(posy) << endl;

}
