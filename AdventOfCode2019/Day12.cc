#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>

using namespace std;

struct data
{
    data(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
    int x;
    int y;
    int z;
    
    void print()
    {
        cout << "<" << x << ", " << y << ", " << z << ">";
    }
    
};

int calcAdjust(int a, int b)
{
    if(a < b)
        return 1;
    else if( a > b)
        return -1;
    else
        return 0;
}

int getAbs(int x, int y, int z)
{
    return abs(x) + abs(y) + abs(z);    
}

void iterateSystem(vector<data>& pos, vector<data>& vel)
{
    vector<data> tempVel = vel;
    for(int i = 0; i < pos.size() - 1; i++)
        for(int j = i+1; j < pos.size(); j++)
        {
            tempVel[i].x += calcAdjust(pos[i].x, pos[j].x);
            tempVel[i].y += calcAdjust(pos[i].y, pos[j].y);
            tempVel[i].z += calcAdjust(pos[i].z, pos[j].z);
            tempVel[j].x += calcAdjust(pos[j].x, pos[i].x);
            tempVel[j].y += calcAdjust(pos[j].y, pos[i].y);
            tempVel[j].z += calcAdjust(pos[j].z, pos[i].z);
        }

    for(int i = 0; i < pos.size(); i++)
    {
        pos[i].x += tempVel[i].x;
        pos[i].y += tempVel[i].y;
        pos[i].z += tempVel[i].z;
    }
    
    vel = tempVel;
}

long gcd(long x, long y)
{
    while(y != 0)
    {
        long temp = y;
        y = x % y;
        x = temp;
    }
    
    return x;
}

long lcm(long x, long y)
{   
    return (x*y)/gcd(x,y);
}

long partTwo(vector<data> pos)
{
    vector<data> vel(pos.size(), {0,0,0});
    vector<data> initialVel = vel;
    vector<data> initialPos = pos;
    
    int cx = 0, cy = 0, cz = 0;
    int counter = 0;
    while(cx == 0 || cy == 0 || cz == 0)
    {
        bool bx = true;
        bool by = true;
        bool bz = true;
        
        iterateSystem(pos, vel);
        counter++;
        
        for(int i = 0; i < pos.size(); i++)
        {
            if(initialPos[i].x != pos[i].x || initialVel[i].x != vel[i].x)
                bx = false;
            if(initialPos[i].y != pos[i].y || initialVel[i].y != vel[i].y)
                by = false;
            if(initialPos[i].z != pos[i].z || initialVel[i].z != vel[i].z)
                bz = false;
        }
        
        if(bx)
            cx = cx != 0 ? cx : counter;
        if(by)
            cy = cy != 0 ? cy : counter;
        if(bz)
            cz = cz != 0 ? cz : counter;
    }
    
    return lcm(cx,lcm(cy,cz));
}


int partOne(vector<data> pos, int iterations)
{
    vector<data> vel(pos.size(), {0,0,0});
    
    for(int iters = 0; iters < iterations; iters++)
        iterateSystem(pos, vel);

    int totalEnergy = 0;
    for(int i = 0; i < pos.size(); i++)
        totalEnergy += getAbs(pos[i].x, pos[i].y, pos[i].z) * getAbs(vel[i].x, vel[i].y, vel[i].z);
        
    return totalEnergy;
}

int main(int arg, char** argc)
{
    
    regex r(".+=(-?[0-9]+).+=(-?[0-9]+).+=(-?[0-9]+).+");
    vector<data> vecData;
    while(!cin.eof())
    {
        string str;
        smatch m;
        getline(cin, str);
        regex_match(str, m, r);
        vecData.push_back({stoi(m[1]), stoi(m[2]), stoi(m[3])});  
    };
    
    cout << "PartOne: " << partOne(vecData, 1000) << endl;    
    cout << "PartTwo: " <<  partTwo(vecData) << endl;

    return 0;
}
