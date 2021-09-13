#include <iostream>

using namespace std;

int main(){
    
//    b = 67;
//    c = 67;
//    if(a != 0) JUMP to A:
// A: b = 67 * 100;
//    b = 1000000 + 67 * 100;
//    c = 1000000 + 67 * 100 + 17000; 
// B: f = 1;
//    d = 2;
// E: e = 2;
// D: g = d * e - b;
//    if(g != 0) JUMP to C
//    f = 0;
// C: e = e++
//    g = e - b;
//    if(g != 0) Jump to D
//    d++;
//    g = d - b
//    if(g != 0) Jump to E
//    if(f != 0) Jump to F
//    h++;
// F: g = b - c
//    if(g != 0) Jump to G
//    Jump to END
// G: b+= 17;
//    Jump to B

    int a = 1;
    long b = 67;
    long c = b;
    long h = 0;
    if(a != 0){
        b = 100 * b + 100000;
        c = b + 17000;
    }
    bool done = false;
    while(!done){
        long f = 1;
        long d = 2;
        
        do{
// checking if b is a product of d*e for e and d -> [2, b].
// Instead of iterating both it is enough to check for reminder == 0
//            long e = 2;
//            do{
//                if(b == d*e){
//                    f = 0;
//                }
//                e++;
//            }
//            while(e != b);
            if((b % d) == 0){
                f = 0; 
                break;
            }
            d++;
        }
        while(b != d);

        if(f == 0){
            h++;
        }
        if(b == c){
            done = true;
        }
        b += 17;
    }

    cout << "PartTwo: " << h << endl;
}
    


