#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
    string str;
    getline(cin, str);
    cout << str.size() << endl;

    long long sum = 0;
    long long sumTwo = 0;
    int n = str.size();
    for(int i = 0; i < n; i++){
        //Partone
        char a = str[i];
        char b = str[(i+1) % (str.size())];
        if(a == b){
            sum += a - '0';
        }
        //PartTwo
        b = str[(i+n/2) % str.size()];
        if(a == b){
            sumTwo += a - '0';
        }
    }

    cout << "PartOne: " << sum << endl;
    cout << "PartTwo: " << sumTwo << endl;
}
