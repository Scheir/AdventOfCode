#include <string>
#include "../../tools/aoc_tools.hpp"
#include <utility>

using namespace std;
using AOC::split;

std::pair<std::string, std::string> day1(const std::string& input) {
   int sum = 0;
   return {to_string(sum + input.size()), "second string"};
}


