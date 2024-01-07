#include <regex>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <type_traits>

using namespace std;

namespace AOC{

/* Get all lines from cin */
vector<string> getLines(){
   string ts;
   vector<string> v;
   while(getline(cin, ts)){
      v.push_back(ts);
   }
   return v;
}

/* Findall implementation below */
/* The idea is to mimic the python implementation
 * of regex.findall(re, str). For each group in
 * the regex you pass as template parameters which type
 * you want to convert the group to. (int, double, str, etc..)
 */

// Type trait used to check if its one or many groups

template <typename T>
T stringToType(const string& s){
   T value;
   stringstream ss(s);
   ss >> value;
   return value;
}

// Helper functions
template <size_t index, typename T>
void groupToValue(T& v, const smatch m){
   v = stringToType<T>(m[index+1].str());
}

template <size_t index, typename... Ts>
void groupsToTuple(tuple<Ts...>& t, const smatch m){
   if constexpr(index < sizeof...(Ts)){
      groupToValue<index>(get<index>(t), m);
      groupsToTuple<index+1, Ts...>(t, m);
   }
}

template<typename... Ts, typename=enable_if_t<sizeof...(Ts) >= 2>>
vector<tuple<Ts...>> findAll(const regex re, string str){
   vector<tuple<Ts...>> v;
   smatch m;
   while(regex_search(str,m,re)){
      tuple<Ts...> groups;
      groupsToTuple<0, Ts...>(groups, m);
      str = m.suffix();
      v.push_back(groups);
   }
   return v;
}

// Specialization for only one group
template <typename T>
vector<T> findAll(const regex re, string str){
   vector<T> v;
   smatch m;
   while(regex_search(str,m,re)){
      stringstream ss(m[1].str());
      T val;
      ss >> val;
      v.push_back(val);
      str = m.suffix();
   }
   return v;
}

/* python split version, (available by default in newer cpp) */
vector<string> split(string str, const string delim){
   vector<string> ret;
   size_t start {0};
   size_t end {str.find(delim)};
   while(end != string::npos){
      string sub = str.substr(start, end-start);
      ret.push_back(sub);
      start = end + delim.size();
      end = str.find(delim, start);
   }
   ret.push_back(str.substr(start));
   return ret;
}

}
