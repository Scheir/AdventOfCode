
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

using namespace std;

constexpr int DIGITS_PER_LAYER = 25*6;
constexpr int DIGITS_PER_ROW = 25;

struct data
{
    data(int z = 0, int o = 0, int t = 0) : zeros(z), ones(o), twos(t) {}
    int zeros;
    int ones;
    int twos;
};

int ctoi(char ch)
{
    return ch - '0';
}

int partOne(string strDigits)
{
    data res(numeric_limits<int>::max());
    data temp;
    for(int i = 0; i < strDigits.size(); i++)
    {
        if(ctoi(strDigits[i]) == 0)
            temp.zeros++;
        else if(ctoi(strDigits[i]) == 1)
            temp.ones++;
        else if(ctoi(strDigits[i]) == 2)
            temp.twos++;

        if((i+1) % (DIGITS_PER_LAYER) == 0)
        {
            res = res.zeros < temp.zeros ? res : temp;
            temp = data();
        }
    }
    
    return res.ones * res.twos;
}



vector<int> getFinalImageVec(string strDigits)
{
    vector<int> vecFinalImage(DIGITS_PER_LAYER,2);
    for(int i = 0; i < strDigits.size(); i++)
    {
        int idx = i % DIGITS_PER_LAYER;
        if(vecFinalImage[idx] == 2 && ctoi(strDigits[i]) == 0)
            vecFinalImage[idx] = 0;
        else if(vecFinalImage[idx] == 2 && ctoi(strDigits[i]) == 1)
            vecFinalImage[idx] = 1;
        else if(ctoi(strDigits[i]) == 2)
            continue;
    }
    return vecFinalImage;
}

void imagePrinter(vector<int>& imageVec)
{
    constexpr char WHITE = '#';
    constexpr char BLACK = ' ';
    for(int i = 0; i < imageVec.size(); i++)
    {
        cout << (imageVec[i] == 0 ? BLACK : WHITE); 
        if((i+1) % DIGITS_PER_ROW == 0)
            cout << endl;
    }
}


void partTwo(string strDigits)
{
    vector<int> imageVec = getFinalImageVec(strDigits);
    imagePrinter(imageVec);
}

int main(int arg, int* argc)
{
    vector<data> vals;
    string strDigits;
    
    while (cin >> strDigits){}
    
    cout << "PartOne: " << partOne(strDigits) << endl;
    cout << "-------- PartTwo --------" << endl; partTwo(strDigits);

}