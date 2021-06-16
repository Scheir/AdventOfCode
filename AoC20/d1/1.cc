#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> v;
    int num = 0;
    while(cin >> num)
    {
        v.push_back(num);
    }
    
    bool done = false;
    for(int i = 0; i < v.size() && !done; i++){
        for(int j = 0; j < v.size(); j++){
            if(i == j)
                continue;
            if(v[i] + v[j] == 2020){
                cout << "PartOne: " << v[i]*v[j] << endl;
                done = true;
            }
        }
    }

   done = false;
   for(int i = 0; i < v.size() && !done; i++){
       for(int j = 0; j < v.size() && !done; j++){
           for(int k = 0; k < v.size() && !done; k++){
               if( i == j || i == k || k == j)
                   continue;
               if(v[i] + v[j] + v[k] == 2020){
                   cout << "PartTwo: " << v[i] * v[j] * v[k] << endl;
                   done = true;
               }
           }
       }
   }
}
