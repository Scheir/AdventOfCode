
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
    int run(queue<int> input);
    void hardReset(vector<int> vec);
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
    void OpCode99(int paramOne, int paramTwo, int paramThree);
    bool isFinnished(){return runFinnished || memoryPointer >= memory.size() || runHalted;}
    int getMemoryPointer(){return memoryPointer;}
    bool getInstruction(int& opCode, string& memoryAdress);
    bool getParameters(int& paramOne, int& paramTwo, int& paramThree, string memoryAdress);
    bool getParameterModeVal(Mode mode, int& param, int paramIdx);
    bool getMemoryAdressString(int memoryPointerVal, string& memoryAdress);
    void softReset();
    void incrementMemoryPointer(int val);
    void setMemoryPointer(int val);
    
private:
    vector<int> memory;
    queue<int> inputs;
    int memoryPointer;
    int programOutput;
    using OpCodeFunMap = map<int,std::function<void(int, int ,int)>>;
    OpCodeFunMap OpFuns;
    bool runFinnished;
    bool runHalted;
    
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
    memoryPointer = 0;
    programOutput = 0;
    runFinnished = false;
    runHalted = false;
}

int IntCodeComputer::run(queue<int> input)
{
    // This is abit weird, maybe remove as member var, or inject it with another call
    // input doesnt feel so runny
    inputs = input;
    // Set startMode (input on website)
    
    // Run the program
    int counter = 0;
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
            cout << "OpCode doesnt match : " << opCode <<  "memoryPointer : " << getMemoryPointer() << endl;
            exit(1);
        }
        // Run instruction
        keyIt->second(paramOne, paramTwo, paramThree);
        counter++;
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

bool IntCodeComputer::getMemoryAdressString(int memoryPointerVal, string& memoryAdress)
{
    //Fill with 0's to allways get 5 digits, 0 is nomrmal mode for non paramer mode.
    string memoryAdressTemp = to_string(memoryPointerVal);
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
    incrementMemoryPointer(4);
}

void IntCodeComputer::OpCode2(int paramOne, int paramTwo, int paramThree)
{
    memory[paramThree] = memory[paramOne]*memory[paramTwo];
    incrementMemoryPointer(4);
}

void IntCodeComputer::OpCode3(int paramOne, int paramTwo, int paramThree)
{
    memory[paramOne] = inputs.front();
    inputs.pop();
    incrementMemoryPointer(2);
}

void IntCodeComputer::OpCode4(int paramOne, int paramTwo, int paramThree)
{
    programOutput = memory[paramOne];
    incrementMemoryPointer(2);
    runFinnished = true;
}

void IntCodeComputer::OpCode5(int paramOne, int paramTwo, int paramThree)
{   
    int val = memory[paramOne] != 0 ? memory[paramTwo] : getMemoryPointer() + 3;
    setMemoryPointer(val);
}

void IntCodeComputer::OpCode6(int paramOne, int paramTwo, int paramThree)
{
    int val = memory[paramOne] == 0 ? memory[paramTwo] : getMemoryPointer() + 3;
    setMemoryPointer(val);
}

void IntCodeComputer::OpCode7(int paramOne, int paramTwo, int paramThree)
{
    memory[paramThree] = memory[paramOne] < memory[paramTwo] ? 1 : 0;
    incrementMemoryPointer(4);
}

void IntCodeComputer::OpCode8(int paramOne, int paramTwo, int paramThree)
{
    memory[paramThree] = memory[paramOne] == memory[paramTwo] ? 1 : 0;
    incrementMemoryPointer(4);
}

void IntCodeComputer::OpCode99(int paramOne, int paramTwo, int paramThree)
{
    runHalted = true;
}

void IntCodeComputer::hardReset(vector<int> vec)
{
    memory = vec;
    memoryPointer = 0;
    programOutput = 0;
    runFinnished = false;
    runHalted = false;
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

bool eq(int a, int b)
{
    return a != b;
}


int partTwo(vector<int> vals)
{
    IntCodeComputer ampA(vals);
    IntCodeComputer ampB(vals);
    IntCodeComputer ampC(vals);
    IntCodeComputer ampD(vals);
    IntCodeComputer ampE(vals);
    
    vector<IntCodeComputer*> vecComp = {&ampA, &ampB, &ampC, &ampD, &ampE};
    int bestRes = 0;
    
    for(int a = 5; a < 10; a++)
        for(int b = 5; b < 10; b++)
            for(int c = 5; c < 10; c++)
                for(int d = 5; d < 10; d++)
                    for(int e = 5; e < 10; e++)
                    {
                        if(eq(a,b) && eq(a,c) && eq(a,d) && eq(a,e) && eq(b,c) && eq(b,d) && eq(b,e) &&
                          eq(c,d) && eq(c,e) && eq(d,e))  
                        {
                            int res = 0;
                            int resE = 0;
                            bool halt = false;
                            for(auto& x : vecComp)
                                x->hardReset(vals);
                                
                            bool first = true;
                            while(!halt)
                            {
                                int idx = 0;
                                for(auto x : {a,b,c,d,e})
                                {
                                    queue<int> input;
                                    
                                    if(first)
                                        input.push(x);
                                    input.push(res);
                                    res = vecComp[idx]->run(input);
                                    if(idx == 4)
                                        resE = res;
                                    if(vecComp[idx]->isHalted())
                                    {
                                        halt = true;
                                        break;
                                    }
                                    idx++;
                                }
                                first = false;
                            }
                            bestRes = bestRes > resE ? bestRes : resE;
                        }
                    }   
    
    return bestRes;                    
}

int partOne(vector<int> vals)
{
    IntCodeComputer haxx0r_3000(vals);
    int bestRes = 0;
    
    for(int a = 0; a < 5; a++)
        for(int b = 0; b < 5; b++)
            for(int c = 0; c < 5; c++)
                for(int d = 0; d < 5; d++)
                    for(int e = 0; e < 5; e++)
                    {
                        if(eq(a,b) && eq(a,c) && eq(a,d) && eq(a,e) && eq(b,c) && eq(b,d) && eq(b,e) &&
                           eq(c,d) && eq(c,e) && eq(d,e))  
                        {
                            int res = 0;
                            for(auto x : {a,b,c,d,e})
                            {
                                queue<int> input;
                                input.push(x); input.push(res);
                                res = haxx0r_3000.run(input);
                                haxx0r_3000.hardReset(vals);
                            }
                            bestRes = bestRes > res ? bestRes : res;
                        }
                    }   
    return bestRes;
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
    
    cout << "PartOne: " << partOne(vals) << endl;
    cout << "PartTwo: " << partTwo(vals) << endl;
}
