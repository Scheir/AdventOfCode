
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> gravityAssistProgram(vector<int> vals)
{
    int idx = 0;
    while(true)
    {
        int pos0 = vals[idx];
        if(pos0 == 99)
        {
            return vals;
            break;
        }
        int pos1 = vals[idx+1];
        int pos2 = vals[idx+2];
        int pos3 = vals[idx+3];
        
        if(pos0 == 1)
        {
            vals[pos3] = vals[pos1]+vals[pos2];
        }
        else if(pos0 == 2)
        {
            vals[pos3] = vals[pos1]*vals[pos2];
        }
        else
        {
            cout << "SOMETHING WENT WRONG" << endl;
            cout << idx << endl;
            exit(0);
        }
        idx += 4;
    }
}

int partOne(vector<int> vals)
{
    // Set initial state
    vals[1] = 12;
    vals[2] = 2;
    return gravityAssistProgram(vals)[0];
}

int partTwo(vector<int> vals)
{
    constexpr int FINAL_VAL = 19690720;
    for(;;)
    {
        for(int noun = 0; noun <= 99; noun++)
        {
            for(int verb = 0; verb <= 99; verb++)
            {
                vector<int> temp = vals;
                temp[1] = noun;
                temp[2] = verb;
                if(gravityAssistProgram(temp)[0] == 19690720)
                    return 100 * noun + verb;
            }
        }
    }
}

int main(int arg, int* argc)
{
    vector<int> vals;
    
    int val;
    while (cin >> val)
    {
        vals.push_back(val);
        if(cin.peek() == ',')
            cin.ignore();
    }
    
    cout << "PartOne: " << partOne(vals) << endl;
    cout << "PartTwo: " << partTwo(vals) << endl;
    
}