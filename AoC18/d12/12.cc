#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;
//initial state: #..#.#..##......###...###
//
//...## => #

int main(){
    string str;
    getline(cin, str);
    string is = str.substr(str.find(":")+2);
    int isSize = is.size();
    map<string,char> m;
    getline(cin ,str);
    while(getline(cin, str)){
        string key = str.substr(0, str.find("=") - 1);
        char val = str[str.size()-1];
        m[key] = val;
    }

    is = "..............................................." + is + "...............................................................................................................................................................";

   // cout << "0: "<< is << endl;
    int start = is.find("#");
    int sum = 0;
    for(int i = 1; i <= 100; i++){
        string temp = is;
        for(auto it = is.begin(); it != is.end()-5; it++){
            string ts(it, it+5);
            char c = '.';
            auto mit = m.find(ts);
            if(mit != m.end())
                c = mit->second;
            int dist = distance(is.begin(), it+2);
            temp[dist] = c;
        }
        is = temp;
       // uncomment to see the pattern printout.
       // cout<< i << ": " << is << endl;
        if(i == 20){
            for(int i = 0; i < is.size(); i++)
                if(is[i] == '#')
                    sum += (i-start);
        }
    }

    cout << "PartOne: " << sum << endl;
    
    //Part two
    //Did not find any clean solution,
    //however, by looking at the print out 
    //after 100 steps it is clear that it is coverging to 
    //to a number of filled pots (185). And there is always 
    //a new pot inserted for each generation. So if potNumber 5 is the 
    //last pot in the initial state, then 50000000000 + 5 is the 
    //last pot after 5000.. generations.
    long lastPot = isSize + 50000000000-1;
    
    long sumP2 = 0;
    for(long i = lastPot; i >= (lastPot - 185); i--)
        sumP2 += i;


    cout << "PartTwo: " << sumP2 << endl;

}
