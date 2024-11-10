#ifndef AOC_TOOLS_HPP
#define AOC_TOOLS_HPP

#include <regex>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>

using namespace std;

namespace AOC{

/* Get all lines from cin */
inline vector<string> getLines(){
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
template <typename T>
inline T stringToType(const string& s){
   T value;
   stringstream ss(s);
   ss >> value;
   return value;
}

template <size_t index, typename T>
inline void groupToValue(T& v, const smatch m){
   v = stringToType<T>(m[index+1].str());
}

template <size_t index, typename... Ts>
inline void groupsToTuple(tuple<Ts...>& t, const smatch m){
   if constexpr(index < sizeof...(Ts)){
      groupToValue<index>(get<index>(t), m);
      groupsToTuple<index+1, Ts...>(t, m);
   }
}

template<typename... Ts>
inline vector<tuple<Ts...>> findAll(const regex re, string str){
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

/* findall implementation when we only have one group */
inline vector<string> findAll(const regex re, string str){
   vector<string> v;
   smatch m;
   while(regex_search(str,m,re)){
      v.push_back(m[1].str());
      str = m.suffix();
   }
   return v;
}

/* python split version, (available by default in newer cpp) */
inline vector<string> split(string str, const string delim){
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


template <typename F, typename... ARGS>
inline void timeIt(F&& f, ARGS&&... args){
   auto start = chrono::high_resolution_clock::now();
   std::invoke(f, args...);
   auto end = chrono::high_resolution_clock::now();
   auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
   cout << "Time: " << duration.count() << " microseconds" << endl;

}

} // namespace AOC

#endif // AOC_TOOLS_HPP
