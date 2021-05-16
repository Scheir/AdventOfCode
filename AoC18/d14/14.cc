#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

int main(){
    int elf1 = 0;
    int elf2 = 1;

    vector<short> vec{3,7};
    //constexpr int recipes = 51589;
    int recipes = 598701;
    string findStr = "598701";
    string recString = "37";
    bool done = false;
    while(!done || vec.size() <= recipes + 10){
        int sum = vec[elf1] + vec[elf2];
        if(sum >= 10){
            int tens = sum/10;
            int ones = sum%10;
            if(recString.size()+2 > findStr.size()){
                recString.erase(recString.begin());
                vec.push_back(tens);
                recString += to_string(tens);
                if(findStr == recString){
                    done = true;
                    cout << "PartTwo: " << vec.size() - findStr.size() <<  endl;
                }

                recString.erase(recString.begin());
                vec.push_back(ones);
                recString += to_string(ones);
                if(findStr == recString){
                    done = true;
                    cout << "PartTwo: " << vec.size() - findStr.size() << endl;
                }
            }
            else{
                recString += to_string(tens) + to_string(ones);
                vec.push_back(tens); vec.push_back(ones);
            }
        }
        else{
            vec.push_back(sum);
            if(recString.size() + 1 > findStr.size())
                recString.erase(recString.begin());
            recString += to_string(sum);
        }
        elf1 = (elf1 + vec[elf1] + 1) % vec.size();
        elf2 = (elf2 + vec[elf2] + 1) % vec.size();
        
        if(recString == findStr){
            done = true;
            cout << "PartTwo: " << vec.size() - findStr.size() << endl;
        }
        assert(elf1 != elf2);

    }

    cout << "PartOne: ";
    for(int i = recipes; i < recipes + 10; i++){
        cout << vec[i];
    }
    cout << endl;

}
