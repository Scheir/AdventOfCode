#include <iostream>
#include <string>

using namespace std;

int main(){
    string str = "";
    getline(cin, str);
    
    int res = 0;
    bool garbage = false;
    int count = 0;
    int countGarbage = 0;
    for(int i = 0; i < str.size(); i++){
        char c = str[i];
        if(c == '!'){
            i++;
        }
        else if(garbage){
            if(c == '>'){
                garbage = false;
            }
            else{
                countGarbage++;
            }
        }
        else{
            if(c == '<'){
                garbage = true;
            }
            else if(c == '{'){
                count++;
                res += count;
            }
            else if(c == '}'){
                count--;
            }
        }
    }

    cout << "PartOne: " << res << endl;
    cout << "PartTwo: " << countGarbage << endl;
}

