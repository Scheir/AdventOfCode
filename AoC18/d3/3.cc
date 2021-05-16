#include<iostream>
#include<vector>
#include<regex>
#include<tuple>

using namespace std;
//#1 @ 1,3: 4x4

int main(){
    vector<tuple<int,int,int,int>> vec;
    // #1 @ 1,3: 4x4
    regex re("[0-9]+");
    smatch m;
    string str;
    while(getline(cin, str)){
        cout << str << endl;
        while(regex_search(str, m, re)){
            cout << m[1] << endl;
            str = m.suffix();
        }
    }
}
