#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int num;
    vector<int> vec;
    while(cin >> num)
        vec.push_back(num);

    int ones = 0;
    int twos = 0;
    int threes = 0;
    vec.push_back(0), vec.push_back(0); vec.push_back(0);
    sort(vec.begin(), vec.end());
    vec.push_back(vec.back()+3);

    for(int i = 0; i < vec.size()-1; i++){
        int diffOne = vec[i+1] - vec[i];
        if(diffOne == 1)
            ones++;
        else if(diffOne == 3)
            threes++;
    }

    cout << "PartOne: " << ones*threes << endl;
    vector<long long> v{0,0,1};

    for(int i = 3; i < vec.size(); i++){
        bool fir = (vec[i] - vec[i-3]) < 4;
        bool sec = (vec[i] - vec[i-2]) < 4;
        bool thi = (vec[i] - vec[i-1]) < 4;
        v.push_back(v[i-3]*fir + v[i-2]*sec + v[i-1]*thi);        

    }
    cout << "PartTwo: " <<  v.back() << endl;
}
