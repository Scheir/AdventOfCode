#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(){
    string str;
    map<char,int> m;
    int sum = 0;
    int sum2 = 0;
    int persons = 0;
    while(getline(cin, str)){
        if(str.size() == 0){
            sum += m.size();   
            for(auto x : m)
            {
                if(x.second == persons)
                    sum2++;
            }
            m.clear();
            persons = 0;
        }
        else{
            persons++;
            for(auto x : str){
                auto it = m.find(x);
                if(it == m.end())
                    m[x] = 1;
                else
                    (it->second)++;
            }
        }
    }
    cout << "PartOne: " << sum << endl;
    cout << "PartTwo: " << sum2 << endl;
}
