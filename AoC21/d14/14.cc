#include <map>
#include <iostream>
#include <string>
#include <regex>

using namespace std;
using ll = long long;


int main(){
	int N = 10;
	map<string,char> rules{};
	string str{""};
	getline(cin, str);
	string ts;
	regex re("([A-Z]+) -> ([A-Z])");
	smatch m;
	while(getline(cin,ts)){
		if(ts == "")
			continue;
		regex_match(ts,m,re);
		rules[m[1]] = m[2].str()[0];
	}	

	map<string,ll> counter{};
	for(int i = 0; i < str.size()-1; i++){
		string chars{str[i], str[i+1]};
		counter[chars] += 1;
	}

	// NN->C => N -> NCN => NN -> NC && CN
	for(int i = 0; i < N; i++){
		map<string,ll> tempCounter{};
		for(auto [key,val] : counter){
			string a{key[0],rules[key]};
			string b{rules[key],key[1]};
			tempCounter[a] += val;
			tempCounter[b] += val;
		}
		counter = tempCounter;
	}
	
	// Count character by character instead of pairs
	map<char,ll> resCounter{};
	for(auto [key,val] : counter){
		resCounter[key.front()] += val;
	}

	// Need to add the last character of string
	resCounter[str.back()] += 1;

	//extract values in resCounter and store them in vector
	// to finally calculate max count - min count
	vector<ll> values{};
	for(auto [_,v]: resCounter)
		values.push_back(v);
	cout << (*max_element(values.begin(), values.end()) - *min_element(values.begin(), values.end())) << endl;
}
