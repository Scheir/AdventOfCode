
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>    
#include <functional>
#include <map>

using namespace std;


constexpr int P_IDX_1 = 1;
constexpr int P_IDX_2 = 2;
constexpr int P_IDX_3 = 3;


enum class Mode
{
    POSITIONAL = 0,
    IMMEDIATE = 1
};


int charDigitToInt(char ch)
{
    return ch - '0';
}

class IntCodeComputer
{
public:
    IntCodeComputer(vector<int> memory_);   
    int run(int startMode = 0);
    
protected:
    void OpCode1(int paramOne, int paramTwo, int paramThree);
    void OpCode2(int paramOne, int paramTwo, int paramThree);
    void OpCode3(int paramOne, int paramTwo, int paramThree);
    void OpCode4(int paramOne, int paramTwo, int paramThree);
    void OpCode5(int paramOne, int paramTwo, int paramThree);
    void OpCode6(int paramOne, int paramTwo, int paramThree);
    void OpCode7(int paramOne, int paramTwo, int paramThree);
    void OpCode8(int paramOne, int paramTwo, int paramThree);
    void OpCode99(int paramOne, int paramTwo, int paramThree);
    bool isFinnished(){return runFinnished || memoryPointer >= memory.size();}
    int getMemoryPointer(){return memoryPointer;}
    bool getInstruction(int& opCode, string& memoryAdress);
    bool getParameters(int& paramOne, int& paramTwo, int& paramThree, string memoryAdress);
    bool getParameterModeVal(Mode mode, int& param, int paramIdx);
    bool getMemoryAdressString(int memoryPointer, string& memoryAdress);
    void reset(vector<int> vec);
    
private:
    vector<int> memory;
    int startMode;
    int memoryPointer = 0;
    int programOutput;
    using OpCodeFunMap = map<int,std::function<void(int, int ,int)>>;
    OpCodeFunMap OpFuns;
    bool runFinnished = false;
    
};

IntCodeComputer::IntCodeComputer(vector<int> memory_) : memory(memory_)
{
    OpFuns[1] = bind(&IntCodeComputer::OpCode1, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[2] = bind(&IntCodeComputer::OpCode2, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[3] = bind(&IntCodeComputer::OpCode3, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[4] = bind(&IntCodeComputer::OpCode4, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[5] = bind(&IntCodeComputer::OpCode5, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[6] = bind(&IntCodeComputer::OpCode6, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[7] = bind(&IntCodeComputer::OpCode7, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[8] = bind(&IntCodeComputer::OpCode8, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
    OpFuns[99] = bind(&IntCodeComputer::OpCode99, this, placeholders::_1,std::placeholders::_2,std::placeholders::_3);
}

int IntCodeComputer::run(int startMode_)
{
    // Reset after run
    vector<int> memoryCpy = memory;
    // Set startMode (input on website)
    startMode = startMode_;
    
    
    // Run the program
    while(!isFinnished())
    {
                
        if(memory.size() <= getMemoryPointer())
        {
            cout << "Memory pointer went to far: " << getMemoryPointer() << endl;
            exit(1);
        }
        
        string memoryAdress = "";
        int memoryAdressVal = memory[getMemoryPointer()];
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

        // Find instuction matching OpCode.
        auto keyIt = OpFuns.find(opCode);
        if(keyIt == OpFuns.end())
        {
            cout << "OpCode doesnt match : " << opCode << endl;
            exit(1);
        }
        
        // Run instruction
        keyIt->second(paramOne, paramTwo, paramThree);
        
        cout << opCode << " : " << paramOne << " : " << paramTwo << " : " << paramThree << " : " << getMemoryPointer() << endl;
    }
    
    reset(memoryCpy);
    return programOutput;
}

bool IntCodeComputer::getInstruction(int& opCode, string& memoryAdress)
{
    
    // opCode are last two digit 000(XX)
    constexpr int SUB_STR_IDX = 3;
    
    if(memoryAdress.size() < 5)
        return false;
    opCode = stoi(memoryAdress.substr(SUB_STR_IDX));
    
    // Can only have 1 - count of functions - 1, no 0, contains 99 also.
    if(opCode != 99 && opCode > OpFuns.size() - 1)
        return false;
    
    // trash the opCode number
    memoryAdress = memoryAdress.substr(0, 3);
    return true;
}

bool IntCodeComputer::getParameters(int& paramOne, int& paramTwo, int& paramThree, string memoryAdress)
{
    // Get Mode for each param, they are the last three digits in the memoryAdress string
    Mode modePar1 = static_cast<Mode>(charDigitToInt(memoryAdress[0]));
    Mode modePar2 = static_cast<Mode>(charDigitToInt(memoryAdress[1]));
    Mode modePar3 = static_cast<Mode>(charDigitToInt(memoryAdress[2]));
    // cout << "mem add: " << memoryAdress << " : " <<int(modePar1) <<" : " <<int(modePar2) << " : " <<int(modePar2)  <<endl; 
    return getParameterModeVal(modePar1, paramOne, P_IDX_1) && 
           getParameterModeVal(modePar2, paramTwo, P_IDX_2) &&
           getParameterModeVal(modePar3, paramThree, P_IDX_3);
    
}

bool IntCodeComputer::getParameterModeVal(Mode mode, int& param, int parameterIndex)
{
    int memPointer = getMemoryPointer();
    bool ok = true;
    switch(mode)
    {
        case Mode::POSITIONAL:
            param =  memory[memPointer+parameterIndex];
            break;
        case Mode::IMMEDIATE:
            param = memPointer+parameterIndex;
            break;
        default:
            ok = false;
    }
}

bool IntCodeComputer::getMemoryAdressString(int memoryPointer, string& memoryAdress)
{
    //Fill with 0's to allways get 5 digits, 0 is nomrmal mode for non paramer mode.
    string memoryAdressTemp = to_string(memoryPointer);
    while(memoryAdressTemp.size() != 5 )
        memoryAdressTemp = "0" + memoryAdressTemp;
    
    // First three digits has to be 0 or 1;
    for(int i = 0; i < memoryAdressTemp.size()-2; i++)
        if(memoryAdressTemp[i] != '0' && memoryAdressTemp[i] != '1')
            return false;
    
    memoryAdress = memoryAdressTemp;
    return true;
}

void IntCodeComputer::OpCode1(int paramOne, int paramTwo, int paramThree)
{
    memory[paramThree] = memory[paramOne]+memory[paramTwo];
    memoryPointer += 4;
}

void IntCodeComputer::OpCode2(int paramOne, int paramTwo, int paramThree)
{
    memory[paramThree] = memory[paramOne]*memory[paramTwo];
    memoryPointer += 4;
}

void IntCodeComputer::OpCode3(int paramOne, int paramTwo, int paramThree)
{
    memory[paramOne] = startMode;
    memoryPointer += 2;
}

void IntCodeComputer::OpCode4(int paramOne, int paramTwo, int paramThree)
{
    programOutput = memory[paramOne];
    memoryPointer += 2;
}

void IntCodeComputer::OpCode5(int paramOne, int paramTwo, int paramThree)
{   
    memoryPointer = memory[paramOne] != 0 ? memory[paramTwo] : memoryPointer + 3;
}

void IntCodeComputer::OpCode6(int paramOne, int paramTwo, int paramThree)
{
    memoryPointer = memory[paramOne] == 0 ? memory[paramTwo] : memoryPointer + 3;
}

void IntCodeComputer::OpCode7(int paramOne, int paramTwo, int paramThree)
{
    memory[paramThree] = memory[paramOne] < memory[paramTwo] ? 1 : 0;
    memoryPointer += 4;
}

void IntCodeComputer::OpCode8(int paramOne, int paramTwo, int paramThree)
{
    memory[paramThree] = memory[paramOne] == memory[paramTwo] ? 1 : 0;
    memoryPointer += 4;
}

void IntCodeComputer::OpCode99(int paramOne, int paramTwo, int paramThree)
{
    runFinnished = true;
}

void IntCodeComputer::reset(vector<int> vec)
{
    memory = vec;
    memoryPointer = 0;
    runFinnished = false;
}

int main(int arg, int* argc)
{
    vector<int> vals;
    int val;
    while (cin >> val)
    {
        vals.push_back(val);
        if(cin.peek() == ',')
            cin.ignore();
    }
    
    IntCodeComputer haxx0r_3000(vals);
    cout << "Run startMode 1 (Part 1): " << haxx0r_3000.run(1) << endl;
    cout << "Run startMode 5 (Part 2): "<< haxx0r_3000.run(5) << endl;
}
