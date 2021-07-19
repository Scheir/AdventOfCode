#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

int main(){
    int target = 325489;
    int currentNumber = 1;
    // Square number where center is 0.
    int id = 0;
    int prevNumber = 1;

    while(target > currentNumber){
        id++;
        prevNumber = currentNumber;
        currentNumber = prevNumber + 8*id;
    } 

    cout << prevNumber << ":" << currentNumber << endl;

    // Line center numbers
    int jump = id*2;
    int a = currentNumber - jump/2;
    int b = currentNumber - jump*2+id;
    int c = currentNumber - jump*3+id;
    int d = currentNumber - jump*4+id;


    // Divide the current square into 4 sections
    // Use the a,b,c or d above depending on where on the square
    // we are.
    double aa = target - prevNumber; 
    double bb = currentNumber - prevNumber;

    int res = 0;
    if(aa/bb <=  0.25){
        res = abs(target-d) + id;
    }
    else if(aa/bb <= 0.5){
        res = abs(target-c) + id;
    }
    else if(aa/bb <= 0.75){
        res = abs(target-b) + id;
    }
    else{
        res = abs(target-a) + id;
    }
    
    cout << "PartOne: " << res << endl;
    
    // Part Two
    vector<vector<int>> vec(10, vector<int>(10,0));
    vec[5][5] = 1;

    int x = 5;
    int y = 5;
    int idx = 1;

    int max = 0;
    bool done = false;
    vector<int> dx = {-1,0,1};
    vector<int> dy = {-1,0,1};

    constexpr int ITERATIONS = 5;
    while(idx < ITERATIONS){
        for(int i = x+idx-1, j = y+idx; i > x-idx; i--){
            int sum = 0;
            for(auto dxx : dx){
                for(auto dyy : dy){
                    if(dyy == 0 && dxx == 0)
                        continue;
                    else
                        sum += vec[i+dxx][j+dyy];
                }
            }
            vec[i][j] = sum;
            if(sum > target){
                cout << "PartTwo: " << sum << endl;
                exit(1);
            }
        }

        for(auto x : vec){
            for(auto xx : x){
                cout << setw(10) <<  xx ;
            }
            cout << endl;
        }
        cout << endl;

        for(int i = x-idx, j = y+idx; j > y-idx ; j--){
            int sum = 0;
            for(auto dxx : dx){
                for(auto dyy : dy){
                    if(dyy == 0 && dxx == 0)
                        continue;
                    else
                        sum += vec[i+dxx][j+dyy];
                }
            }
            vec[i][j] = sum;
            if(sum > target){
                cout << "PartTwo: " << sum << endl;
                exit(1);
            }
        }
        for(auto x : vec){
            for(auto xx : x){
                cout << setw(10) <<  xx ;
            }
            cout << endl;
        }
        cout << endl;
                
        for(int i = x-idx, j = y-idx; i < x+idx; i++){
            int sum = 0;
            for(auto dxx : dx){
                for(auto dyy : dy){
                    if(dyy == 0 && dxx == 0)
                        continue;
                    else
                        sum += vec[i+dxx][j+dyy];
                }
            }
            vec[i][j] = sum;
            if(sum > target){
                cout << "PartTwo: " << sum << endl;
                exit(1);
            }
        }

        for(auto x : vec){
            for(auto xx : x){
                cout << setw(10) <<  xx ;
            }
            cout << endl;
        }
        cout << endl;
        for(int i = x+idx, j = y-idx; j <= y+idx; j++){
            int sum = 0;
            for(auto dxx : dx){
                for(auto dyy : dy){
                    if(dyy == 0 && dxx == 0)
                        continue;
                    else
                        sum += vec[i+dxx][j+dyy];
                }
            }
            vec[i][j] = sum;
            if(sum > target){
                cout << "PartTwo: " << sum << endl;
                exit(1);
            }
        }

        for(auto x : vec){
            for(auto xx : x){
                cout << setw(10) <<  xx ;
            }
            cout << endl;
        }
        cout << endl;
        idx++;
    }
}
