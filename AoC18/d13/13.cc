#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum direction{
    dleft = 0,
    straight = 1,
    dright = 2
};

struct cart{
    cart(char c_, int x_, int y_) : c(c_), x(x_), y(y_) {}
    char c;
    direction dir = dleft;
    int x;
    int y;
    bool operator<(const cart& other) const{
        if(x < other.x)
            return true;
        else if(x == other.x)
            return y < other.y;
        else
            return false;
    }
    void intersectionTurn(){
        direction tdir = dir;
        dir = static_cast<direction>((static_cast<int>(dir)+1) % 3);
        switch(tdir){
            case dleft:
                if(c == '>'){
                    c = '^';
                    return; 
                }
                else if(c == '^'){
                    c = '<';
                    return ;
                }
                else if(c == '<'){
                    c = 'v';
                    return ;
                }
                else if( c == 'v'){
                    c = '>';
                    return ;
                }
            case straight:
                if(c == '>'){
                    c = '>';
                    return ;
                }
                else if(c == '^'){
                    c = '^';
                    return ;
                }
                else if(c == '<'){
                    c = '<';
                    return ;
                }
                else if( c == 'v'){
                    c = 'v';
                    return ;
                }
            case dright:
                if(c == '>'){
                    c = 'v';
                    return ;
                }
                else if(c == '^'){
                    c = '>';
                    return ;
                }
                else if(c == '<'){
                    c = '^';
                    return ;
                }
                else if( c == 'v'){
                    c = '<';
                    return ;
                }
        }
    }

    void turn(char mapCh){
        if(mapCh == '+')
            intersectionTurn();
        if(mapCh == '/'){
            if(c == '>')
                c = '^';
            else if(c == 'v')
                c = '<';
            else if(c == '<')
                c = 'v';
            else
                c = '>';
        }
        if(mapCh == '\\'){
            if(c == '<')
                c = '^';
            else if(c == 'v')
                c = '>';
            else if(c == '>')
                c = 'v';
            else
                c = '<';
        }
    }

    void move(){
        if(c == '>')
            y++;
        if(c == '<')
            y--;
        if(c == '^')
            x--;
        if(c == 'v')
            x++;
    } 
};

void printTick(vector<string> vs, vector<cart>& vc){
    for(auto x : vc){
        vs[x.x][x.y] = x.c;
    }

    cout << endl;
    for(auto x : vs)
        cout << x << endl;
}

bool findCrash(vector<cart>& vc, int& winnerx, int& winnery){
    for(int i = 0; i < vc.size(); i++){
        for(int j = 0; j < vc.size(); j++){
            if(j != i){
                if(vc[i].x == vc[j].x && vc[i].y == vc[j].y){
                    winnerx = vc[i].x; winnery = vc[i].y;
                    if(i > j){
                        vc.erase(find_if(vc.begin(), vc.end(), [&](cart c){return vc[i].x == c.x && vc[i].y == c.y;}));
                        vc.erase(find_if(vc.begin(), vc.end(), [&](cart c){return vc[j].x == c.x && vc[j].y == c.y;}));
                    }
                    else{
                        vc.erase(find_if(vc.begin(), vc.end(), [&](cart c){return vc[j].x == c.x && vc[j].y == c.y;}));
                        vc.erase(find_if(vc.begin(), vc.end(), [&](cart c){return vc[i].x == c.x && vc[i].y == c.y;}));
                    }
                    return true;
                }
            }
        }
    }
}

int main(){
    vector<string> vec;
    string str;
    while(getline(cin, str)){
        vec.push_back(str);
    }
    vector<cart> carts;
    vector<string> noArrows = vec;
    for(int i = 0; i < noArrows.size(); i++){
        for(int j = 0; j < noArrows[0].size(); j++){
            if(noArrows[i][j] == '>'){
                carts.push_back({'>',i,j});
                noArrows[i][j] = '-';
            }
            if(noArrows[i][j] == '<'){
                carts.push_back({'<',i,j});
                noArrows[i][j] = '-';
            }
            if(noArrows[i][j] == '^'){
                carts.push_back({'^',i,j});
                noArrows[i][j] = '|';
            }
            if(noArrows[i][j] == 'v'){
                carts.push_back({'v',i,j});
                noArrows[i][j] = '|';
            }
        }
    }

    bool p1 = true;
    int winnerx = 0;
    int winnery = 0;

    while(carts.size()!= 1){
        sort(carts.begin(), carts.end());
        for(auto& x : carts){
            x.turn(noArrows[x.x][x.y]);
            x.move();
            if(findCrash(carts, winnerx, winnery)){
                if(p1){
                    cout << "PartOne: " << winnery << "," << winnerx << endl;
                    p1 = false;
                }
            }

        }
    }
    
    cout << "PartTwo: " << carts[0].y << "," << carts[0].x << endl;
    return 0;
}
