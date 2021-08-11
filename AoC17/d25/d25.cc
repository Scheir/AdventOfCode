#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <tuple>

using namespace std;

struct state{
    char n;
    tuple<int,char,char> pos;
    tuple<int,char,char> neg;
    state(char name, tuple<int,char,char> ne, tuple<int,char,char> po) : n(name), neg(ne), pos(po){}
};

int main(){
    state A('A', {1,'R','B'}, {1,'L','E'});
    state B('B', {1,'R','C'}, {1,'R','F'});
    state C('C', {1,'L','D'}, {0,'R','B'});
    state D('D', {1,'R','E'}, {0,'L','C'});
    state E('E', {1,'L','A'}, {0,'R','D'});
    state F('F', {1,'R','A'}, {1,'R','C'});
    
    vector<state> vs;
    vs.push_back(A); vs.push_back(B); vs.push_back(C); vs.push_back(D); vs.push_back(E); vs.push_back(F);

    int n = 100000000;
    vector<int> vec(n,0);
    int idx = n/2; 
    int steps = 12459852;
    char cur = 'A';

    for(int i = 0; i < steps; i++){
        int slotVal = vec[idx];
        auto it = find_if(vs.begin(), vs.end(), [cur](state s){
            return s.n == cur;
        });
        if(slotVal == 0){
            vec[idx] = get<0>(it->neg);
            idx = get<1>(it->neg) == 'R' ? idx+1 : idx-1;
            cur = get<2>(it->neg);
        }
        if(slotVal == 1){
            vec[idx] = get<0>(it->pos);
            idx = get<1>(it->pos) == 'R' ? idx+1 : idx-1;
            cur = get<2>(it->pos);
        }
    }
    int res = count(vec.begin(), vec.end(), 1);
    cout << "PartOne: " << res << endl;
}


        

