#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>   
#include <functional>
#include <map>
#include <queue>
 
using namespace std;
 
 
constexpr int P_IDX_1 = 1;
constexpr int P_IDX_2 = 2;
constexpr int P_IDX_3 = 3;
 
enum class Mode
{
    POSITIONAL = 0,
    IMMEDIATE = 1,
    RELATIVE = 2,
    UP_LIMIT = 3
};
 
 
int charDigitToInt(char ch)
{
    return ch - '0';
}
 
class IntCodeComputer
{
public:
    IntCodeComputer(vector<long long>& memory_);  
    long long run(queue<int> input);
    void hardReset(vector<long long>& vec);
    bool isHalted(){return runHalted;}
   
protected:
    void OpCode1(int paramOne, int paramTwo, int paramThree);
    void OpCode2(int paramOne, int paramTwo, int paramThree);
    void OpCode3(int paramOne, int paramTwo, int paramThree);
    void OpCode4(int paramOne, int paramTwo, int paramThree);
    void OpCode5(int paramOne, int paramTwo, int paramThree);
    void OpCode6(int paramOne, int paramTwo, int paramThree);
    void OpCode7(int paramOne, int paramTwo, int paramThree);
    void OpCode8(int paramOne, int paramTwo, int paramThree);
    void OpCode9(int paramOne, int paramTwo, int paramThree);
    void OpCode99(int paramOne, int paramTwo, int paramThree);
    bool isFinnished(){return runFinnished || runHalted;}
    int getMemoryPointer(){return memoryPointer;}
    bool getInstruction(int& opCode, string& memoryAdress);
    bool getParameters(int& paramOne, int& paramTwo, int& paramThree, string memoryAdress);
    bool getParameterModeVal(Mode mode, int& param, int paramIdx);
    bool getMemoryAdressString(long long memoryPointerVal, string& memoryAdress);
    void softReset();
    void incrementMemoryPointer(int val);
    void setMemoryPointer(int val);
    void adjustRelativeBase(long long val);
    long long readMemory(int memoryAdress);
    void setMemory(long long adress, long long val);
   
private:
    vector<long long> memory;
    queue<int> inputs;
    int memoryPointer;
    long long programOutput;
    using OpCodeFunMap = map<int,std::function<void(int, int ,int)>>;
    OpCodeFunMap OpFuns;
    bool runFinnished;
    bool runHalted;
    int relativeBase;
   
};
 
IntCodeComputer::IntCodeComputer(vector<long long>& memory_) : memory(memory_)
{
    OpFuns[1] = bind(&IntCodeComputer::OpCode1, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[2] = bind(&IntCodeComputer::OpCode2, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[3] = bind(&IntCodeComputer::OpCode3, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[4] = bind(&IntCodeComputer::OpCode4, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[5] = bind(&IntCodeComputer::OpCode5, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[6] = bind(&IntCodeComputer::OpCode6, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[7] = bind(&IntCodeComputer::OpCode7, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[8] = bind(&IntCodeComputer::OpCode8, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[9] = bind(&IntCodeComputer::OpCode9, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[99] = bind(&IntCodeComputer::OpCode99, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    memoryPointer = 0;
    programOutput = 0;
    runFinnished = false;
    runHalted = false;
    relativeBase = 0;
}
 
long long IntCodeComputer::readMemory(int memoryAdress)
{
    // Add memory if needed
    while(memory.size() <= memoryAdress)
    {
        memory.push_back(0);
    }

    return memory[memoryAdress];
}

void IntCodeComputer::setMemory(long long adress, long long val)
{
    // Add memory if needed
    while(memory.size() <= adress)
    {
        memory.push_back(0);
    }
    memory[adress] = val;
}
 
long long IntCodeComputer::run(queue<int> input)
{
    inputs = input;
    // Run the program
    while(!isFinnished())
    {
        string memoryAdress = "";
        long memoryAdressVal = readMemory(getMemoryPointer());
        if(!getMemoryAdressString(memoryAdressVal, memoryAdress))
        {
            cout << "Failed in getting memoryAdresString at memory: " << getMemoryPointer() <<endl;
            exit(1);
        }
       
        int opCode = 0;
        if(!getInstruction(opCode, memoryAdress))
        {
            cout << "Failed in getting instruction at memory: " << getMemoryPointer() <<endl;
            exit(1);
        }
       
        int paramOne, paramTwo, paramThree;
        if(!getParameters(paramOne, paramTwo, paramThree, memoryAdress))
        {
            cout << "Failed in getting paramers at menory: " << getMemoryPointer() <<endl;
            exit(1);
        }

        auto keyIt = OpFuns.find(opCode);
        if(keyIt == OpFuns.end())
        {
             cout << "OpCode doesnt match : " << opCode <<  "memoryPointer : " << getMemoryPointer() << endl;
            exit(1);
        }
        // Run instruction
        keyIt->second(paramOne, paramTwo, paramThree);
    }
   
    softReset();

    return programOutput;
}
 
bool IntCodeComputer::getInstruction(int& opCode, string& memoryAdress)
{
   
    // opCode are last two digit ABC(XX)
    // ABC are modes for params 3/2/1
    constexpr int SUB_STR_IDX = 3;
    if(memoryAdress.size() < 5)
        return false;
    opCode = stoi(memoryAdress.substr(SUB_STR_IDX));
   
    // Can only be within count of functions, contains 99 also.
    if(opCode != 99 && opCode > OpFuns.size() )
        return false;
   
    // trash the opCode number
    memoryAdress = memoryAdress.substr(0, 3);
    return true;
}
 
bool IntCodeComputer::getParameters(int& paramOne, int& paramTwo, int& paramThree, string memoryAdress)
{
    // If there are other then 3 digits left in string, something went wrong.
    if(memoryAdress.size() != 3)
        return false;
       
    // Get Mode for each param, they are the last three digits in the memoryAdress string
    // memoryAdress = [mode param3, mode param2, mode param 1]
    Mode modePar1 = static_cast<Mode>(charDigitToInt(memoryAdress[2]));
    Mode modePar2 = static_cast<Mode>(charDigitToInt(memoryAdress[1]));
    Mode modePar3 = static_cast<Mode>(charDigitToInt(memoryAdress[0]));
    bool ok = getParameterModeVal(modePar1, paramOne, P_IDX_1) &&
              getParameterModeVal(modePar2, paramTwo, P_IDX_2) &&
              getParameterModeVal(modePar3, paramThree, P_IDX_3);
   
    return ok;
   
}
 
bool IntCodeComputer::getParameterModeVal(Mode mode, int& param, int parameterIndex)
{
    int memPointer = getMemoryPointer();
    bool ok = true;
    switch(mode)
    {
        case Mode::POSITIONAL:
            param = readMemory(memPointer+parameterIndex);
            break;
        case Mode::IMMEDIATE:
            param = memPointer + parameterIndex;
            break;
        case Mode::RELATIVE:
            param = readMemory(memPointer + parameterIndex) + relativeBase;
            break;
        default:
            ok = false;
    }
    return ok;
}
 
bool IntCodeComputer::getMemoryAdressString(long long memoryPointerVal, string& memoryAdress)
{
    //Fill with 0's to allways get 5 digits, 0 is nomrmal mode for non paramer mode.
    string memoryAdressTemp = to_string(memoryPointerVal);
    while(memoryAdressTemp.size() != 5 )
        memoryAdressTemp = "0" + memoryAdressTemp;
   
    // First three digits has to be 0 or 1;
    for(int i = 0; i < memoryAdressTemp.size()-2; i++)
        if(charDigitToInt(memoryAdressTemp[i]) >= static_cast<int>(Mode::UP_LIMIT))
            return false;
   
    memoryAdress = memoryAdressTemp;
    return true;
}
 
void IntCodeComputer::OpCode1(int paramOne, int paramTwo, int paramThree)
{
    long long val = readMemory(paramOne)+readMemory(paramTwo);
    setMemory(paramThree, val);
    incrementMemoryPointer(4);
}
 
void IntCodeComputer::OpCode2(int paramOne, int paramTwo, int paramThree)
{
    long long val = readMemory(paramOne)*readMemory(paramTwo);
    setMemory(paramThree, val);
    incrementMemoryPointer(4);
}
 
void IntCodeComputer::OpCode3(int paramOne, int paramTwo, int paramThree)
{
    setMemory(paramOne, inputs.front());
    inputs.pop();
    incrementMemoryPointer(2);
}
 
void IntCodeComputer::OpCode4(int paramOne, int paramTwo, int paramThree)
{
    programOutput = readMemory(paramOne);
    incrementMemoryPointer(2);
    // runFinnished = true;
}
 
void IntCodeComputer::OpCode5(int paramOne, int paramTwo, int paramThree)
{  
    long long val = readMemory(paramOne) != 0 ? readMemory(paramTwo) : getMemoryPointer() + 3;
    setMemoryPointer(val);
}
 
void IntCodeComputer::OpCode6(int paramOne, int paramTwo, int paramThree)
{
    long long val = readMemory(paramOne) == 0 ? readMemory(paramTwo) : getMemoryPointer() + 3;
    setMemoryPointer(val);
}
 
void IntCodeComputer::OpCode7(int paramOne, int paramTwo, int paramThree)
{
    long long val = readMemory(paramOne) < readMemory(paramTwo) ? 1 : 0;
    setMemory(paramThree, val);
    incrementMemoryPointer(4);
}
 
void IntCodeComputer::OpCode8(int paramOne, int paramTwo, int paramThree)
{
    long long val = readMemory(paramOne) == readMemory(paramTwo) ? 1 : 0;
    setMemory(paramThree, val);
    incrementMemoryPointer(4);
}
 
void IntCodeComputer::OpCode9(int paramOne, int paramTwo, int paramThree)
{
    adjustRelativeBase(readMemory(paramOne));
    incrementMemoryPointer(2);
}
 
void IntCodeComputer::OpCode99(int paramOne, int paramTwo, int paramThree)
{
    runHalted = true;
}
 
void IntCodeComputer::hardReset(vector<long long>& vec)
{
    memory = vec;
    memoryPointer = 0;
    programOutput = 0;
    runFinnished = false;
    runHalted = false;
    relativeBase = 0;
}
 
 
void IntCodeComputer::softReset()
{
    runFinnished = false;
}
 
 
void IntCodeComputer::incrementMemoryPointer(int val)
{
    memoryPointer += val;
}
 
void IntCodeComputer::setMemoryPointer(int val)
{
    memoryPointer = val;
}
 
void IntCodeComputer::adjustRelativeBase(long long val)
{
    relativeBase += val;
}
 
int main(int arg, char** argc)
{
    vector<long long> vals;
    long long val;
    while (cin >> val)
    {
        vals.push_back(val);
        if(cin.peek() == ',')
            cin.ignore();
    }
   
    queue<int> q;
    q.push(2);
   
    IntCodeComputer haxxor_3000(vals);
    cout << haxxor_3000.run(q) << endl;
}
