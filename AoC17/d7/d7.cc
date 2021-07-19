#include <iostream>
#include <numeric>
#include <limits>
#include <vector>
#include <string>
#include <regex>
#include <utility>
#include <algorithm>

using namespace std;

//Recursively find the bottom node
string findBottom(vector<tuple<string, int, vector<string>>>& vec, string searchName){
    auto it = find_if(vec.begin(), vec.end(), [searchName](tuple<string, int, vector<string>> t){
        auto children = get<2>(t);
        auto itChild = find_if(children.begin(), children.end(), [searchName](string str){
            return str == searchName;});

        return itChild != children.end();
    });
    if(it == vec.end()){
        return searchName;
    }        
    else{
        return findBottom(vec, get<0>(*it));
    }
} 

// Recursively find the accumulated balance for the input node (searchName). Children + node weight included.
int findWrongBalance(vector<tuple<string, int, vector<string>>>& vec, string searchName){
    auto it = find_if(vec.begin(), vec.end(), [searchName](tuple<string, int, vector<string>> t){
        string name = get<0>(t);
        return name == searchName;
    });

    int balance = get<1>(*it);
    auto children = get<2>(*it);
    
    if(children.size() == 0)
        return balance;

    for(auto child : children){
        balance += findWrongBalance(vec, child);
    }

    return balance;
}
        
   

int main(){
    regex word("([a-z]+)");
    regex number("([0-9]+)");
    smatch m;

    vector<tuple<string, int, vector<string>>> vec;
    string str;
    while(getline(cin, str)){
        string name;
        int num;
        vector<string> children;
        regex_search(str, m, word);
        name = m[1];
        str = m.suffix();
        regex_search(str, m, number);
        num = stoi(m[1].str());
        str = m.suffix();
        while(regex_search(str, m, word)){
            string temp = m[1];
            children.push_back(temp);
            str = m.suffix();
        }
        
        vec.push_back({name, num, children});
    }
    
    string searchName = "";
    int low = numeric_limits<int>::max(); 
    for(auto x : vec){
       int temp = get<1>(x);
       if(temp < low){
           searchName = get<0>(x);
           low = temp;
       }
    }

    string bottom = findBottom(vec, searchName);

    cout << "PartOne: " << bottom << endl;

    // Part Two
    bool done = false;
    string search = bottom;
    int res = 0;

    // start at the top and serach each children if there is a missmatch.
    // We need to find the last node which doesnt have children that has a missmatch in weight,
    // then we know the node before the nonmissmatching children is the one we have to change.
    while(!done){
        auto it = find_if(vec.begin(), vec.end(), [search](tuple<string, int, vector<string>> t){
            string name = get<0>(t);
            return name == search;
        });
        auto children = get<2>(*it);
        vector<int> balances;
        for(auto child : children){
            balances.push_back(findWrongBalance(vec, child));
        }

        int l = numeric_limits<int>::max();
        int h = 0;
        string tempName = "";
        for(int i = 0; i < balances.size(); i++){
            int temp = balances[i];
            if(temp > h){
                h = temp;
                tempName = children[i];
            }
            else{
                l = temp;
            }
        }
        
        // If the highest and the lowest element in the balance vector are the same,
        // then we know that there is no miss match for the searched node.
        // Exit the loop, and use the results from the previous node, which is the 
        // node where the unbalace is. If that one is balanced, according to the assignment,
        // all the previous nodes should also be fixed as there is only one miss weighted node.
        if(h == l){
            done = true;
            break;
        }
        
        it = find_if(vec.begin(), vec.end(), [tempName](tuple<string, int, vector<string>> t){
            string name = get<0>(t);
            return name == tempName;
        });
        
        // The answer should be the node weight subtracted by the difference to get balance.
        int balance = get<1>(*it);
        res = balance - (h - l);
        search = tempName;
    }

    cout << "PartTwo: " << res << endl;
}
        
