#include <string>
#include <ctype.h>
#include <iostream>
#include <algorithm>

using namespace std;

void solve(string& str, int idx){
    if(idx >= str.size())
        return;
    if((toupper(str[idx]) == str[idx+1] || str[idx] == toupper(str[idx+1])) && (str[idx] != str[idx+1])){
        str.erase(idx,2);
        if(idx != 0)
            idx = idx - 2;
    }
    solve(str, idx+1);
}

int main(){
    string str;
    while(cin >> str)

    solve(str, 0);
    cout << "PartOne: " << str.size() << endl;
    
    string newStr = str;
    for(auto& x : str)
        x = toupper(x);
    sort(str.begin(), str.end());
    str.erase(unique(str.begin(), str.end()), str.end());
    
    int winner = newStr.size();
    for(auto x : str){
        string temp = newStr;
        temp.erase(remove(temp.begin(), temp.end(), x), temp.end()); 
        temp.erase(remove(temp.begin(), temp.end(),tolower(x)), temp.end());
        solve(temp, 0);
        winner = winner < temp.size() ? winner : temp.size();
    }
    cout << "PartTwo: " << winner << endl;
}
