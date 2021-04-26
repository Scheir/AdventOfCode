#include <iostream> 
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>    
#include <functional>
#include <map>
#include <queue> 
#include <tuple>
#include <set>
#include <list>

using namespace std;


static set<double> upSet;
static set<double> lowSet;

double calculateSlope(int curentX, int curentY, int targetX, int targetY)
{
    double dx = targetX - curentX;
    double dy = curentY - targetY;
    double res = 0;
    if(dx == 0.0)
        res = dy > 0.0 ? numeric_limits<double>::max() : numeric_limits<double>::min();
    else if(dy == 0.0)
       res = dx > 0.0 ? 10e-4: -10e-4; // small enough to not interfere with non 0 values
    else
        res = dy/dx;
    
    return res;
}

double pointDistance(int curX, int tarX, int curY, int tarY)
{
    return sqrt(pow(curX-tarX,2) + pow(curY-tarY,2));
}

tuple<int,int,int> partOne(vector<string> lines)
{
    tuple<int,int,int> cordsAndRes {0,0,0};
    for(int i = 0; i < lines.size(); i++)
    {
        for(int j = 0; j < lines[0].size(); j++)
        {
            if(lines[i][j] == '.')
                continue;
                
            set<double> upperSet, lowerSet;
            for(int k = 0; k < lines.size(); k++)
            {
                for(int l = 0; l < lines.size(); l++)
                {
                    if(i == k && j == l)
                        continue;
                    else if(lines[k][l] == '.')
                        continue;
                    else
                    {
                        // Divide map into two parts, otherwise we will only get
                        // one of possibly two astroids with the same slope.
                        if(k < i)
                            upperSet.insert(calculateSlope(j,i,l,k));
                        else
                            lowerSet.insert(calculateSlope(j,i,l,k));
                    }
                }   
            }

            int tempRes = upperSet.size() + lowerSet.size();
            if(get<2>(cordsAndRes) < tempRes)
            {
                cordsAndRes = {j,i,tempRes};
                upSet = upperSet;
                lowSet = lowerSet;
            }
        }
    }
    
    return cordsAndRes;
}

int partTwo(vector<string> lines, int stationX, int stationY, int meteorNumber)
{
    if(meteorNumber < 1)
    {
        cout << "Meteor numbering starts from 1" << endl;
        exit(1);
    }
    vector<double> allSlopes;
    
    //Place slopes in clockwise order from POV of station, starting at "12".
    //Top right
    for(auto it = upSet.rbegin(); it != upSet.rend(); it++)
        if(*it > 0)
            allSlopes.push_back(*it);
    
    //Bottom right
    for(auto it = lowSet.rbegin(); it != lowSet.rend(); it++)
        if(*it < 0)
            allSlopes.push_back(*it);
    
    //Bottom left
    for(auto it = lowSet.rbegin(); it != lowSet.rend(); it++)
        if(*it > 0)
            allSlopes.push_back(*it);
        
    //Top left    
    for(auto it = upSet.rbegin(); it != upSet.rend(); it++)
        if(*it < 0)
            allSlopes.push_back(*it);
    
    double closestDistance = numeric_limits<double>::max();
    int resX, resY;
    for(int i = 0; i < lines.size(); i++)
    {
        for(int j = 0; j < lines.size(); j++)
        {
            if(lines[i][j] == '.')
                continue;
            else
            {
                if(calculateSlope(stationX, stationY, j, i) == allSlopes[meteorNumber-1])
                {
                    int tempDistance = pointDistance(stationX, j, stationY, i);
                    closestDistance = closestDistance < tempDistance ? closestDistance : tempDistance; 
                    resX = j;
                    resY = i;
                }
            }
        }   
    }
    return resX*100 + resY;
}

int main(int arg, int* argc)
{
    vector<string> lines;
    string tempString;
    while (cin >> tempString)
    {
        if(cin.peek() == '\n' || cin.eof())
        {
            lines.push_back(tempString);
            tempString.clear();
            cin.ignore();
        }
    }
    
    auto coordAndRes = partOne(lines);
    cout << "PartOne: " << get<2>(coordAndRes) << endl;
    cout << "PartTwo: " << partTwo(lines, get<0>(coordAndRes), get<1>(coordAndRes), 200) << endl;
}
