#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <limits>

using namespace std;

long long mul_inv(long long a, long long b)
{
    long long b0{ b }, t{ 0 }, q{ 0 };
    long long x0{ 0 }, x1{ 1 };

    if (b == 1){
        return 1;
    }
    while (a > 1){ 
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0){
        x1 += b0;
    }

    return x1;
}


long long chinese_remainder(const std::vector<long long>& n, const std::vector<long long>& a, const long long lenght){
    long long p{ 0 }, i{ 0 }, prod{ 1 }, sum{ 0 };
    for (i = 0; i < lenght; i++){
        prod *= n[i];
    }

    for(i = 0; i < lenght; i++){ 
        p = prod / n[i];
        sum += a[i] * mul_inv(p, n[i]) * p;
    }

    return sum % prod;
}

int main(){
    string str;
    getline(cin, str);
    int ts = stoi(str);
    vector<long long> vec;
    //Needed for part two
    int idx = -1;
    vector<long long> pos;
    while(getline(cin, str, ',')){
        idx++;
        if(str == "x")
            continue;
        vec.push_back(stoi(str));
        pos.push_back(idx);
    }

    int winner = numeric_limits<int>::max();
    int winnerts = 0;
    for(auto x : vec){
        int idx = 1;
        int twinner = 0;
        while(twinner <= ts){
            twinner = x*idx;
            idx++;
        }
        if(winner > twinner-ts){
            winner = twinner-ts;
            winnerts = x;
        }
    }
    cout << "PartOne: " << winner*winnerts << endl;

    // Part two stuff
    auto it = max_element(pos.begin(), pos.end());

    // Reminder should be high on the first time stamp and low on the last
    int maxPos = *it;
    for(auto& x : pos)
        x = maxPos - x; 

     
    // Solve the modulus equation
    long long res = chinese_remainder(vec, pos, vec.size());
    
    // We solve for the greatest pos in the vector, so need to subtract all minutes(idx)
    // from the result to get the first timestamp.
    for(auto x : pos)
        cout << x << ",";
    cout << endl;
    cout << "Res before subtracting: " << res << endl;
    res = res - idx;
    cout << "PartTwo: " << res << endl;

}
