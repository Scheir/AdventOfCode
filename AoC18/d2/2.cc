#include<string>
#include<iostream>
#include<algorithm>
#include<limits>

using namespace std;
int main(){
    
    string str;
    vector<string> lines;
    while(getline(cin, str))
        lines.push_back(str); 

    int twoCount = 0; int threeCount = 0;
    for(auto line: lines){
        bool isThree = false;
        bool isTwo = false;
        for(auto ch : line){
            int count = count_if(line.begin(), line.end(), [ch](char compChar) {return ch == compChar;});
            if(count == 3)
                isThree = true;
            else if(count == 2)
                isTwo = true;
        }
        if(isThree)
            threeCount++;
        if(isTwo)
            twoCount++;
    }
    cout << "PartOne: " << twoCount * threeCount << endl;

    char diffChar;
    sort(lines.begin(), lines.end());
    auto it = adjacent_find(lines.begin(), lines.end(), [&](string a, string b){
        int count = 0;
        for(int i = 0; i < a.size();i++){
            bool m = a[i] == b[i];
            count += m;
            if(!m)
                diffChar = a[i];
            }
        return count == a.size() - 1;
    });

    (*it).erase(remove((*it).begin(), (*it).end(), diffChar));

    cout << "PartTwo: " << *it << endl;
}
