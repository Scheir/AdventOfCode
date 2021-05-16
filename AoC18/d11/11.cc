#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// X = 3 , y = 5
/*The rack ID is 3 + 10 = 13.
The power level starts at 13 * 5 = 65.
Adding the serial number produces 65 + 8 = 73.
Multiplying by the rack ID produces 73 * 13 = 949.
The hundreds digit of 949 is 9.
Subtracting 5 produces 9 - 5 = 4.
*/

constexpr int serialNo = 8199;
int calcPower(int x, int y){
    int rackId = x + 10;
    int powerLevel = rackId * y;
    int addSerial = powerLevel + serialNo;
    int multRackId = addSerial * rackId;
    string str  = to_string(multRackId);
    int hundredDig = str[str.size()-3] - '0';
    return (str[str.size()-3] - '0') - 5;
}

int main(){
   
    // add 0 row and column to skip if statement for bounds in part 2.
    vector<vector<int>> mat(301, vector<int>(301, 0)); 
    for(int i = 1; i <= 300; i++){
        for(int j = 1; j <= 300; j++){
            mat[i-1][j-1] = calcPower(j,i);
        }
    }

    int winner = 0;
    int winnerx = 0;
    int winnery = 0;
    for(int y = 0; y < 298; y++){
        for(int x = 0; x < 298; x++){
            int sum = mat[y][x] + mat[y+1][x] + mat[y+2][x] + mat[y][x+1] + mat[y+1][x+1] +
                      mat[y+2][x+1] + mat[y][x+2] + mat[y+1][x+2] + mat[y+2][x+2];
            if(winner < sum){
                winner = sum;
                winnerx = x+1;
                winnery = y+1;
            }
        }
    }
    cout <<"PartOne: " << winnerx << "," << winnery << ". Winner sum is: " << winner << endl;

    // Calculate summed area table 
    for(int i = 1; i < mat.size(); i++){
        for(int j = 1; j < mat.size(); j++){
            mat[i][j] = mat[i][j] + mat[i-1][j] + mat[i][j-1] - mat[i-1][j-1];
        }
    }
    
    int winnerp2 = 0;
    int winneri = 0;
    for(int i = 2; i < 300; i++){
        for(int y = i; y < mat.size(); y++){
            for(int x = i; x < mat.size(); x++){
                int sum = mat[y][x] - mat[y-i][x] - mat[y][x-i] + mat[y-i][x-i];
                if(winnerp2 < sum){
                    winneri = i;
                    winnerx = x-i+2; // +2 for left top corner, since there is a
                    winnery = y-i+2; // 0 row and 0 column and counting starts from x,y = 1.
                    winnerp2 = sum;
                }
            }
        }
    }
    cout << "PartTwo: " << winnerx << ","<< winnery << ","<< winneri << ".  winnerp2: " << winnerp2 << endl;
}

