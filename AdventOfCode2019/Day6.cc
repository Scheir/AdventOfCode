
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <limits>

using namespace std;

static int res = 0;

void findCount(string input, vector<pair<string,string>>& vecPair, int counter)
{
    counter++;
    for(int i = vecPair.size()-1; i >= 0; i--)
    {
        if(vecPair[i].first == input)   
            findCount(vecPair[i].second, vecPair, counter);
    }
    res += counter;
};

 // Find the first node in the orbit tree
string getFirstNode(vector<pair<string,string>>& vecPair)
{   
    for(auto&x : vecPair)
    {
        if(find_if(vecPair.begin(), vecPair.end(), [x](pair<string,string> p)
        {
            return x.first == p.second;
        }) == vecPair.end())
        {
            return x.second;
        }
    }       
}


string findPreviousOrbit(string input, vector<pair<string,string>>& vecPair)
{
    string tempString = "";     
    auto it = find_if(vecPair.begin(), vecPair.end(), [input](pair<string,string> p)
    {
        return input == p.second;
    });
    
    tempString = (*it).first;
    return tempString;
    
}

vector<string> getPathToStart(vector<pair<string,string>>& vecPair, string input)
{
    const string firstNode = getFirstNode(vecPair);
    string curentOrbit = input;
    vector<string> v;
    while(curentOrbit != firstNode)
    {
        curentOrbit = findPreviousOrbit(curentOrbit, vecPair);
        v.push_back(curentOrbit);
    }
    
    return v;
}

int partOne(vector<pair<string,string>> vecPair)
{
    string firstNode = getFirstNode(vecPair);
    findCount(firstNode, vecPair, 0);
    return res;
}

int partTwo(vector<pair<string,string>>& vecPair)
{
    vector<string> vecYou = getPathToStart(vecPair, "YOU");
    vector<string> vecSan = getPathToStart(vecPair, "SAN");
    
    int score = numeric_limits<int>::max();
    for(int i = 0; i < vecYou.size(); i++)
    {
        auto it = find(vecSan.begin(), vecSan.end(), vecYou[i]);
        if(it == vecSan.end())
            continue;
        else
        {
            int tempScore = i + distance(vecSan.begin(), it);
            score = score < tempScore ? score : tempScore;
        }
    }
    return score; 
}

int main(int arg, int* argc)
{
    vector<pair<string,string>> vecPair;
    while(!cin.eof())
    {
        string str;
        getline(cin, str);
        int brace = str.find(")");
        vecPair.push_back({str.substr(0,brace), str.substr(brace+1)});
    }
    
    cout << "PartOne: " << partOne(vecPair) << endl;
    cout << "PartTwo: " << partTwo(vecPair) << endl;
}
