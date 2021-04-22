
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
    
    tempVec.push_back({0,0});
    for(auto& ele : vec)
    {
        char dir = ele[0];
        int length = stoi(ele.substr(1));
        if(dir == 'U')
        {
            // for(int i = y+1; i <= y + length; i++)
            // {
            //     tempVec.push_back({i,x});
            // }
            tempVec.push_back({x,y+length});
            y += length;
        }
        
        else if(dir == 'D')
        {
            // for(int i = y-1; i >= y - length; i--)
            // {
            //     tempVec.push_back({i,x});
            // }
            tempVec.push_back({x, y-length});
            y -= length;
        }
        
        else if(dir == 'R')
        {
            // for(int i = x+1; i <= x + length; i++)
            // {
            //     tempVec.push_back({y,i});
            // }
            tempVec.push_back({x+length, y});
            x += length;
        }
        
        else if(dir == 'L')
        {
            // for(int i = x-1; i >= x - length; i--)
            // {
            //     tempVec.push_back({y,i});
            // }
            tempVec.push_back({x-length, y});
            x -= length;
        }
    }
    
    return tempVec;
}

vector<pair<int,int>> findIntersections(vector<pair<int,int>>& vecPair, vector<string> wire)
{
    int x = 0;
    int y = 0;
    vector<pair<int,int>> tempVec;
    
    
    // for(auto& x : vecPair)
    //     cout << "{" << x.first << "," << x.second << "}" << " , ";
    // cout << endl;
    for(auto & ele : wire)
    {
        // cout << ele << endl;
        char dir = ele[0];
        int length = stoi(ele.substr(1));
        
        // cout << x << " : " << y << " : " << length << endl;
        
        for(int i = 0; i < vecPair.size() - 1; i++)
        {
            pair<int,int> p1 = vecPair[i];
            pair<int,int> p2 = vecPair[i+1];
            bool isVertical  = p1.first == p2.first;
            if( dir == 'U' && !isVertical)
            {
                bool px = p1.first < p2.first;
                if(y < p1.second && p1.second < y+length) 
                {
                    if(px && x > p1.first && x < p2.first)
                    {
                            tempVec.push_back({x, p1.second});    
                    }
                    if(!px && x < p1.first && x > p2.first)
                    {
                            tempVec.push_back({x, p2.second});    
                    }
                }
            }
            if(dir == 'D' && !isVertical)
            {
                bool px = p1.first < p2.first;
                if(y-length < p1.second && p1.second < y) 
                {
                    if(px && x > p1.first && x < p2.first)
                    {
                            tempVec.push_back({x, p1.second});    
                    }
                    if(!px && x < p1.first && x > p2.first)
                    {
                            tempVec.push_back({x, p1.second});    
                    }
                }
            }
            if(dir == 'R' && isVertical)
            {
                bool py = p1.second < p2.second;
                if(x < p1.first && p1.first < x+length) 
                {
                    if(py && y > p1.second && y < p2.second)
                    {
                            tempVec.push_back({p1.first, y});    
                    }
                    if(!py && y < p1.second && y > p2.second)
                    {
                            tempVec.push_back({p1.first, y});    
                    }
                }
                
            }
            if(dir == 'L' && isVertical)
            {
                bool py = p1.second < p2.second;
                if(x-length < p1.first && p1.first < x) 
                {
                    if(py && y > p1.second && y < p2.second)
                    {
                            tempVec.push_back({p1.first, y});    
                    }
                    if(!py && y < p1.second && y > p2.second)
                    {
                            tempVec.push_back({p1.first, y});    
                    }
                }
            }
        }
        
        if(dir == 'U' || dir == 'D') 
            y = dir == 'U' ? y + length : y - length; 
        if(dir == 'R' || dir == 'L')
            x = dir == 'R' ? x + length : x - length; 
    }
    
    return tempVec;
}

vector<int> solve(vector<string> inputLine)
{
    vector<string> wireOne = parsedWire(inputLine[0]);
    vector<string> wireTwo = parsedWire(inputLine[1]);

    auto wirePairVec1 = getWireLocationVec(wireOne);
    
    auto intersections = findIntersections(wirePairVec1, wireTwo);
    
    // for(auto& x : intersections)
    //     cout << "{" << x.first << "," << x.second << "}" << " , ";
    
    cout << endl;
    // auto wirePairVec2 = getWireLocationVec(wireTwo);
    
    // For partTwo
    // auto cpyWire1 = wirePairVec1;
    // auto cpyWire2 = wirePairVec2;
    
    // Sort and remove duplicates
    // sort(wirePairVec1.begin(), wirePairVec1.end());
    // sort(wirePairVec2.begin(), wirePairVec2.end());
    // wirePairVec1.erase(unique(wirePairVec1.begin(), wirePairVec1.end()), wirePairVec1.end());
    // wirePairVec2.erase(unique(wirePairVec2.begin(), wirePairVec2.end()), wirePairVec2.end());
    
    // Stack both vectors into one, sort. If duplicated => intersection.
    // wirePairVec1.insert(wirePairVec1.end(), wirePairVec2.begin(), wirePairVec2.end());
    // sort(wirePairVec1.begin(), wirePairVec1.end());
    
    // Find closest (smalles manhattan distance) intersection
    int manhattanDistance = numeric_limits<int>::max();
    
    //Part 2
    // int walkingDistance = numeric_limits<int>::max();
    for(int i = 0; i < intersections.size(); i++)
    {
        // if(wirePairVec1[i] == wirePairVec1[i+1]) // maybe
        // {
            // part 1
            int tempManhattanDistance = abs(intersections[i].first) + abs(intersections[i].second);
            manhattanDistance = manhattanDistance < tempManhattanDistance ? manhattanDistance : tempManhattanDistance;
            
        //     part 2
        //     auto itWire1 = find(cpyWire1.begin(), cpyWire1.end(), wirePairVec1[i]);
        //     auto itWire2 = find(cpyWire2.begin(), cpyWire2.end(), wirePairVec1[i]);
        //     int tempWalkingDistance = distance(cpyWire1.begin(), itWire1) + distance(cpyWire2.begin(), itWire2);
        //     walkingDistance = walkingDistance < tempWalkingDistance ? walkingDistance : tempWalkingDistance;
        // }
    }
    
    // +2 for the first step from origin for both wires.
     return {manhattanDistance, 2};
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
    
    //solve(lines);

    cout << "PartOne: " << solve(lines)[0] << endl << "PartTwo: " << solve(lines)[1] <<endl;
    
    
}