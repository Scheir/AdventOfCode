
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>    

using namespace std;

int IntCodeComputer(vector<int> vals, int input)
{
    int idx = 0;
    int output = 0;
    while(true)
    {
        string modeStr = to_string(vals[idx]);
        int pos0 = vals[idx];
        int pos1 = vals[idx+1];
        int pos2 = vals[idx+2];
        int pos3 = vals[idx+3];
        
        // Parameter mode
        if(modeStr.size() > 2)
        {
            while(modeStr.size() != 5 )
                modeStr = "0" + modeStr;
                
            pos0 = modeStr[4] - '0';
            pos1 = modeStr[2] == '0' ? vals[idx+1] : idx+1;
            pos2 = modeStr[1] == '0' ? vals[idx+2] : idx+2;
            pos3 = modeStr[0] == '0' ? vals[idx+3] : idx+3;
        }
        
        if(pos0 == 99)
        {
            break;
        }
   
        else if(pos0 == 1)
        {
            vals[pos3] = vals[pos1]+vals[pos2];
            idx += 4;
        }
        else if(pos0 == 2)
        {
            vals[pos3] = vals[pos1]*vals[pos2];
            idx += 4;
        }
        else if(pos0 == 3)
        {
            vals[pos1] = input;
            idx +=2;
        }
        else if(pos0 == 4)
        {
            output = vals[pos1];
            idx += 2;
        }
        else if(pos0 == 5)
        {
            if(vals[pos1] != 0)
                idx = vals[pos2];
            else
                idx += 3;
        }
        else if(pos0 == 6)
        {
            if(vals[pos1] == 0)
                idx = vals[pos2];
            else
                idx += 3;
        }
        else if(pos0 == 7)
        {
             if(vals[pos1] < vals[pos2])
                vals[pos3] = 1;
            else
                vals[pos3] = 0;
            idx += 4;
        }
        else if(pos0 == 8)
        {
            if(vals[pos1] == vals[pos2])
                vals[pos3] = 1;
            else
                vals[pos3] = 0;
            idx += 4;
        }
        else
        {
            cout << "SOMETHING WENT WRONG" << endl;
            cout << idx << endl;
            exit(0);
        }
        if (idx >= vals.size())
            exit(2);
    }
    
    return output;
}


int main(int arg, int* argc)
{
    vector<int> vals;
    constexpr int PART_ONE = 1;
    constexpr int PART_TWO = 5;
    int val;
    while (cin >> val)
    {
        vals.push_back(val);
        if(cin.peek() == ',')
            cin.ignore();
    }
    
    cout << "PartOne: " << IntCodeComputer(vals, PART_ONE) << endl;
    cout << "PartTwo: " << IntCodeComputer(vals, PART_TWO) << endl;

}