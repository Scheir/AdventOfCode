#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<string> v;
    string str;
    
    v.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

    while(getline(cin, str)){
        v.push_back("x"+str+"x");
    }
    
    v.push_back("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");

    vector<string> temp;
    vector<int> dx {-1,0,1};
    vector<int> dy {-1,0,1};
    for(int i = 0; i < 10; i++){
        temp = v;
        for(int j = 1; j < v.size()-1; j++){
            for(int k = 1; k < v[j].size()-1; k++){
                int trees = 0;
                int lumber = 0;
                for(auto x : dx){
                    for(auto y : dy){
                        char ch = v[j+x][k+y];
                        if(x == 0 && y == 0)
                            continue;
                        if(ch == '|')
                            trees++;
                        else if(ch == '#')
                            lumber++;
                    }
                }

                char c = v[j][k];
                if(c == '.'){
                    if(trees >= 3)
                        temp[j][k] = '|';
                }
                else if(c == '|'){
                    if(lumber >= 3)
                        temp[j][k] = '#';
                }
                else if(c == '#'){
                    if(lumber >= 1 && trees >= 1){
                        temp[j][k] = '#';
                    }
                    else{
                        temp[j][k] = '.';
                    }
                }
            }
        }
        v = temp;
    }

    int sumTrees = 0;
    int sumLumber = 0;
    for(auto x : v){
        for(auto y : x){
            if(y == '|')
                sumTrees++;
            if(y == '#')
                sumLumber++;
        }
    }

    cout << "PartOne: " << sumTrees*sumLumber << endl;
}
