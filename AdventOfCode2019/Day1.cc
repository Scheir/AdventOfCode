
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;


int getMass(double val)
{
    int divisor = 3;
    int subConst = 2;
    
    return int(val/divisor - subConst);
}

long partOne(vector<double> vec)
{
    long sum = 0;
    for(auto& x : vec)
    {
        sum += getMass(x);
    }
    return sum;
}

long partTwo(vector<double> vec)
{
    long sum = 0;
    
    for(auto& x : vec)
    {
        long unitSum = getMass(x);
        while(unitSum > 0)
        {
            sum += unitSum;
            unitSum = getMass(unitSum);
        }
    }
    return sum;
}

int main(int arg, int* argc)
{
    vector<double> vals;
    
    long sum = 0;
    while (!cin.eof())
    {
        string str;
        getline(cin, str);
        vals.push_back(double(stoi(str)));
    }
    
    cout << "part 1: " << partOne(vals) << endl;
    cout << "part 2: " << partTwo(vals) << endl;
    
}