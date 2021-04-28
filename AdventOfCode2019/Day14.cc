#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>
#include <map>
 
using namespace std;
 
constexpr long ONE_TRIL = 1000000000000;

struct data
{
    data(vector<pair<string,int>> vec)
    {
        for(auto it = vec.rbegin(); it != vec.rend(); it++)
        {
            if(it == vec.rbegin())
            {
                amount = (*it).second;
                chem = (*it).first;
            }
            else
                ingr.insert(*it);
        }
        stock = 0;
    }
   
    bool operator==(string str)
    {
        return chem == str;
    }
    long stock;
    long amount;
    string chem;
    map<string,long> ingr;
};
 

long solve(vector<data>& vec, string searchChem, long chemNeeded)
{
    long res = 0;

    auto it = find(vec.begin(), vec.end(), searchChem);
    long x = chemNeeded-(*it).stock; long y = (*it).amount;
    long reactions = (x/y) + static_cast<int>((x % y) != 0);
    (*it).stock += (*it).amount * reactions;

    for(auto x : (*it).ingr)
    {
        x.second *= reactions;
        auto itNext = find(vec.begin(), vec.end(), x.first);
        if(itNext == vec.end()) // ORE case
        {
            res += x.second;
            return res;
        }
        if((*itNext).stock < x.second)
            res += solve(vec, x.first, x.second);
        (*itNext).stock -= x.second;
    }
    return res;
}

long binarySearch(vector<data> vecData,long low, long high)
{
    while(high - low > 1)
    {   auto vec = vecData;
        int curent = (high + low) / 2;
        if(solve(vec, "FUEL", curent) <= ONE_TRIL)
            low = curent;
        else
            high = curent;
    }
    return low;
}
 
long partOne(vector<data> vecData)
{
   return solve(vecData, "FUEL", 1);
}

long partTwo(vector<data> vecData, long solPartOne)
{
    // Didnt find any elegant solution =>
    // Estimate of fuel with 1000000000000 ORE
    // get actualy number of ORE needed for the estimated fuel
    long res = 0;
    long estimatedFuel = ONE_TRIL/solPartOne;
    auto vec = vecData;
    res = solve(vec, "FUEL", estimatedFuel);
    long actualOreForEstimatedFuel = res;

    // Find ratio and get an even better estimate
    double offset = (double)ONE_TRIL/(double)actualOreForEstimatedFuel;
    long binaryLow = estimatedFuel*offset;
    
    // Since the estimate is only almost perfect brute force
    // (binary search) is needed 
    return binarySearch(vecData, binaryLow, binaryLow+20);
}

int main(int arg, char** argc)
{

    regex r("([0-9]+) ([A-Z]+)");
    vector<data> vecData;
    while(!cin.eof())
    {
        string str;
        smatch m;
        getline(cin, str);
        vector<pair<string,int>> vPair;
        while(regex_search(str, m, r))
        {
            vPair.push_back(make_pair(m[2].str(), stoi(m[1].str())));
            str = m.suffix();
        }
        vecData.push_back(data(vPair));
    }

    auto p1 = partOne(vecData);
    cout << "PartOne: " << p1 << endl;
    cout << "PartTwo: " << partTwo(vecData, p1) << endl;

    return 0;
}
