
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>    

using namespace std;

vector<string> parsedWire(string str)
{
    stringstream ss(str);
    vector<string> vecStr;
    while(ss.good())
    {
        string tempStr;
        getline(ss, tempStr, ',');
        vecStr.push_back(tempStr);
    }
    
    return vecStr;
}

vector<pair<int,int>> getWireLocationVec(vector<string> vec)
{
    vector<pair<int,int>> tempVec;
    
    int x = 0;
    int y = 0;
    
    for(auto& ele : vec)
    {
        char dir = ele[0];
        int length = stoi(ele.substr(1));
        if(dir == 'U')
        {
            for(int i = y+1; i <= y + length; i++)
            {
                tempVec.push_back({i,x});
            }
            y += length;
        }
        
        else if(dir == 'D')
        {
            for(int i = y-1; i >= y - length; i--)
            {
                tempVec.push_back({i,x});
            }
            y -= length;
        }
        
        else if(dir == 'R')
        {
            for(int i = x+1; i <= x + length; i++)
            {
                tempVec.push_back({y,i});
            }
            x += length;
        }
        
        else if(dir == 'L')
        {
            for(int i = x-1; i >= x - length; i--)
            {
                tempVec.push_back({y,i});
            }
            x -= length;
        }
    }
    
    return tempVec;
}

vector<int> solve(vector<string> inputLine)
{
    vector<string> wireOne = parsedWire(inputLine[0]);
    vector<string> wireTwo = parsedWire(inputLine[1]);

    auto wirePairVec1 = getWireLocationVec(wireOne);
    auto wirePairVec2 = getWireLocationVec(wireTwo);
    
    // For partTwo
    auto cpyWire1 = wirePairVec1;
    auto cpyWire2 = wirePairVec2;
    
    // Sort and remove duplicates
    sort(wirePairVec1.begin(), wirePairVec1.end());
    sort(wirePairVec2.begin(), wirePairVec2.end());
    wirePairVec1.erase(unique(wirePairVec1.begin(), wirePairVec1.end()), wirePairVec1.end());
    wirePairVec2.erase(unique(wirePairVec2.begin(), wirePairVec2.end()), wirePairVec2.end());
    
    // Stack both vectors into one, sort. If duplicated => intersection.
    wirePairVec1.insert(wirePairVec1.end(), wirePairVec2.begin(), wirePairVec2.end());
    sort(wirePairVec1.begin(), wirePairVec1.end());
    
    // Find closest (smalles manhattan distance) intersection
    int manhattanDistance = numeric_limits<int>::max();
    int walkingDistance = numeric_limits<int>::max();
    for(int i = 0; i < wirePairVec1.size()-1; i++)
    {
        if(wirePairVec1[i] == wirePairVec1[i+1])
        {
            // part 1
            int tempManhattanDistance = abs(wirePairVec1[i].first) + abs(wirePairVec1[i].second);
            manhattanDistance = manhattanDistance < tempManhattanDistance ? manhattanDistance : tempManhattanDistance;
            
            // part 2
            auto itWire1 = find(cpyWire1.begin(), cpyWire1.end(), wirePairVec1[i]);
            auto itWire2 = find(cpyWire2.begin(), cpyWire2.end(), wirePairVec1[i]);
            int tempWalkingDistance = distance(cpyWire1.begin(), itWire1) + distance(cpyWire2.begin(), itWire2);
            walkingDistance = walkingDistance < tempWalkingDistance ? walkingDistance : tempWalkingDistance;
        }
    }
    
    // +2 for the first step from origin for both wires.
    return {manhattanDistance, walkingDistance+2};
}


int main(int arg, int* argc)
{
    vector<string> lines;
    
    while (!cin.eof())
    {
        string line;
        getline(cin, line);
        lines.push_back(line);
    }

    cout << "PartOne: " << solve(lines)[0] << endl << "PartTwo: " << solve(lines)[1] <<endl;
    
    
}