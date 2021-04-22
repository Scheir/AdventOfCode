
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>    

using namespace std;

bool checkIfAdjacentDuplicate(string str)
{
    for(int i = 0; i < str.size()-1; i++)
    {
        if(str[i] == str[i+1])
            return true;
    }
    
    return false;
}

bool checkIfAdjacentDuplicateExactly2(string str)
{   
    string newStr = "." + str + ".";
    for(int i = 1; i < newStr.size()-2; i++)
    {
        if(newStr[i] == newStr[i+1] && newStr[i-1] != newStr[i] && newStr[i+1] != newStr[i+2])
            return true;
    }
    
    return false;
}

bool checkIfNoDecrease(string str)
{
    for(int i = 0; i < str.size() - 1; i++)
    {
        if((int)str[i] > (int)str[i+1])
            return false;
    }
    
    return true;
}

int partOne(int lb, int ub)
{
    int res = 0;
    
    for(int i = lb; i <= ub; i++)
    {
        string digits = to_string(i);
        if(checkIfNoDecrease(digits) && checkIfAdjacentDuplicate(digits))
            res++;
    }
    
    return res;
}

int partTwo(int lb, int ub)
{
    int res = 0;
    
    for(int i = lb; i <= ub; i++)
    {
        string digits = to_string(i);
        if(checkIfNoDecrease(digits) && checkIfAdjacentDuplicateExactly2(digits))
            res++;
    }
    
    return res;
}

int main(int arg, int* argc)
{
    cout << "Part 1: " << partOne(168630, 718098) << endl;
    cout << "Part 2: " << partTwo(168630, 718098) << endl;
}