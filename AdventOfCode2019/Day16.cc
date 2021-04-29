#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <algorithm>
#include <map>
 
using namespace std;
 
constexpr int repeat = 10000;
constexpr int phases = 100;

int charToDigit(char ch)
{
    return ch -'0';
}

vector<int> createPattern(int numbers)
{
    vector<int> patternTemplate {0, 1, 0, -1};
    vector<int> pattern;
    for(int i = 0; i < numbers; i++)
    {    
        int idx = 0;
        for(int j = 0; j <= numbers;)
        {   
            for(int k = 0; k < i + 1 && j <= numbers; k++)
            {    
                if(j != 0)
                {
                    pattern.push_back(patternTemplate[idx%patternTemplate.size()]);
                }
                j++;
            }
            idx++;
        }
    }
    return pattern;
}
void fft(vector<int>& number, vector<int>& pattern)
{   
    // Pretty messy solution. This can most likely be done in a much more 
    // elegant way.
    for(int j = 0; j < phases; j++)
    {
        vector<int> tempVec; 
        int tempNo = 0;
        for(int i = 1; i <= pattern.size(); i++) 
        {   
            tempNo += number[(i-1)%(number.size())] * pattern[i-1];
            if((i % (number.size())) == 0)
            {
                tempVec.push_back(abs(tempNo)%10);
                tempNo = 0;
            }
        }
        number = tempVec;
    }
}

void fftPartTwo(vector<int>& vec1, vector<int>& vec2)
{
    int sum = 0;
    for(int i = vec1.size() - 1; i >= 0; i--)
    {
        sum += vec1[i];
        vec2[i] = sum%10;
    }
}


int partOne(vector<int> number)
{
    auto pattern = createPattern(number.size());
    fft(number, pattern);
    int res = 0;
    for(int idx = 7, i = 0; idx >= 0; idx--, i++)
    {
        res += number[idx] * pow(10, i);
    }
    return res;
}

int partTwo(vector<int> number)
{
    long offset = 0;
    for(int idx = 6, i = 0; idx >= 0; idx--, i++)
    {
        offset += number[idx] * pow(10, i);
    }

    long totNumbers = number.size() * repeat;  
    long neededNumbers = totNumbers - offset;
    
    // The two vectors in the array will altenate as temp and main vector.
    vector<int> vec[2];
    vec[0].reserve(neededNumbers);
    vec[1].reserve(neededNumbers); 
    while(vec[0].size() != neededNumbers)
    {
        for(auto it = number.rbegin(); it != number.rend() && vec[0].size() != neededNumbers; it++)
            vec[0].push_back(*it);
    }
    // Since elements are added from the back of numbers reverse is needed here.
    reverse(vec[0].begin(), vec[0].end()); 


    vec[1] = vector<int>(vec[0].size(), 0);

    for(int i = 0; i < phases; i++)
    {
        int idx1 = i & 1; // if last bit i is 1 => odd
        int idx2 = idx1 ^ 1; // Both bits same => 0. So, opposite of above.
        fftPartTwo(vec[idx1], vec[idx2]);
    }

    int res = 0;
    for(int idx = 7, i = 0; idx >= 0; idx--, i++)
    {   
        // End at i = 99 (odd) in the above loop, so even (0) is last "target" vector.
        res += vec[0][idx] * pow(10, i);
    }
    return res;
}

int main(int arg, char** argc)
{

    string str;

    vector<int> pattern, number;
    while(cin >> str)
    for(auto x : str)
        number.push_back(charToDigit(x));

    cout << "PartOne: " << partOne(number) << endl;
    cout << "PartTwo: " << partTwo(number) << endl;

    return 0;
}
