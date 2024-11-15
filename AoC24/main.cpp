#include <iostream>
#include <string>
#include <utility>

extern std::pair<std::string, std::string> day1(const std::string&);
extern std::pair<std::string, std::string> day2(const std::string&);

std::pair<std::string, std::string>runDay(int day) {
   switch (day) {
       case 1: return day1("input"); break;
       case 2: return day2("input"); break;
       default:
           std::cerr << "Invalid day selected.\n";
           exit(1);
   }
}

void printer(const std::pair<std::string,std::string>& result, const uint16_t day) {
   std::cout << "Day " << day << std::endl;
   std::cout << "part one: " << result.first << std::endl;
   std::cout << "part two: " << result.second << std::endl;
}

int main(int argc, char** argv) {
   if (argc != 3 || std::string(argv[1]) != "--day") {
      std::cerr << "Usage: " << argv[0] << " --day <day_number>\n";
      return 1;
   }
   const uint16_t day = std::stoi(argv[2]);
   if(day < 1 || day > 25) {
      std::cerr << "Invalid day selected.\n";
      return 1;
   }

   auto res = runDay(day);

   printer(res, day);
   return 0;
}

