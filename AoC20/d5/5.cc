#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getRow(string row){
    string binStrRow = ""; 
    for(auto x : row){
        binStrRow += x == 'F' ? "0" : "1";
    }
    return stoi(binStrRow, 0, 2);
}

int getSeat(string seat){
    string binStrSeat = "";
    for(auto x : seat){
        binStrSeat += x == 'L' ? "0" : "1";   
    }
    return stoi(binStrSeat, 0, 2);
}

int main(){
    string str;
    int winner = 0;
    vector<int> tickets;
    while(getline(cin, str)){
        string row(str.begin(), str.end()-3);
        string seat(str.end()-3, str.end());
        int currentTicket = getRow(row) * 8 + getSeat(seat);
        tickets.push_back(currentTicket);
        winner = currentTicket > winner ? currentTicket : winner; 
    }
    cout << "PartOne: " << winner << endl;

    // Part Two.
    sort(tickets.begin(), tickets.end());
    for(int i = 0; i < tickets.size(); i++){
        if(tickets[i+1] - tickets[i] == 2){
            cout << "PartTwo: " << tickets[i]+1 << endl;
            exit(0);
        }
    }

}
