#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

int main(){
    string str;
    int res = 0;
    int res2 = 0;

    while(getline(cin, str)){
        int dash = str.find("-");
        int space = str.find(" ");
        int colon = str.find(":"); 
        int lower = stoi(str.substr(0,dash));
        int upper = stoi(str.substr(dash+1, space-1));
        char ch = (str.substr(space+1, space+2))[0]; 
        string s = str.substr(colon+2, str.size() - (colon + 2));

        int tot = count(s.begin(), s.end(), ch);
        if(lower <= tot && tot <= upper)
            res++;
        bool first = s[lower-1] == ch;
        bool second = s[upper-1] == ch;

        if((first && !second) || (!first && second))
            res2++;
    }

    cout << "PartOne: " << res << endl;
    cout << "PartTwo: " << res2 << endl;
}



