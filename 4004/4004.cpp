// Include local header files
#include "4004.h"

// Include gloabl header files

// Declaring namespaces
using namespace std;


Intel4004::Intel4004(){}

Intel4004::~Intel4004() {}

void Intel4004::reset() {}

bool Intel4004::getCarry() const {
    return carryFlag;
}

uint4_t Intel4004::getAccumulator() const {
    return accumulator;
}

UBankedAddress Intel4004::getPC() const {}

uint4_t Intel4004::getRegister(const ERegister reg) {}
uint8_t Intel4004::getRegisterPair(const ERegister reg) {}
Intel4001Base* Intel4004::getPtrToROM() {
    return ROM;
}

Intel4002Base* Intel4004::getPtrToRAM() {
    return RAM;
}

Intel4004StackBase* Intel4004::getPtrToStack() {
    return stack;
}

uint64_t Intel4004::getTicks() const {}
void Intel4004::resetTicks() {}
bool Intel4004::getTestPin() const {
    return testPin;
}

void Intel4004::setTestPin(const bool value) {
    testPin = value;
}

void Intel4004::nextCommand() {}
/******* Intel4004 Instructions Set **********/
void Intel4004::NOP()
{
    ticks++;
}

void Intel4004::LDM(UCommand command)
{
    uint4_t value = command.nibble.opa;
    //Clear accumulator
    accumulator = 0;
    accumulator = value;
    ticks++;
}

void Intel4004::LD(UCommand command)
{
    uint4_t registerNumber = command.nibble.opa;
    //Clear accumulator
    accumulator = 0;
    accumulator = registers[registerNumber];
    ticks++;
}

void Intel4004::XCH(UCommand command)
{
    uint4_t registerNumber = command.nibble.opa;
    uint4_t temp = accumulator;
    accumulator = 0;
    accumulator = registers[registerNumber];
    registers[registerNumber] = temp;
    ticks++;
}

void Intel4004::ADD(UCommand command)
{
    uint4_t registerNumber = command.nibble.opa;
    accumulator = accumulator + registers[registerNumber] + carryFlag;    
    carryFlag = accumulator >> 4;
    //reset bits 4-7
    accumulator &= ~(0b11110000);
    ticks++;
}

void Intel4004::SUB(UCommand command)
{
    uint4_t registerNumber = command.nibble.opa;
    uint4_t registerValue = registers[registerNumber];
    //Create ones complement
    registerValue ^= 0b1111;
    accumulator = accumulator + registerValue + !carryFlag; 
    carryFlag = !(accumulator >> 4);
    //reset bits 4-7
    accumulator &= ~(0b11110000);
    ticks++;
}

void Intel4004::INC(UCommand command)
{
    uint4_t registerNumber = command.nibble.opa;
    registers[registerNumber] = registers[registerNumber] + 1;
    if(registers[registerNumber] >> 4)
    {
        registers[registerNumber] = 0;
    }
    ticks++;
}

void Intel4004::BBL(UCommand command)
{
    //reset accumulator
    accumulator = 0;
    accumulator = command.nibble.opa;
    PC = stack->pop();
    ticks++;
}

void Intel4004::JIN(UCommand command)
{
    //Get the 3 bits for registerpair
    uint4_t registerPair = (command.nibble.opa >> 1) & 0b0111;
    uint8_t valueOfRegisterPair = getRegisterPair(ERegister(registerPair));
    PC.banked.address = valueOfRegisterPair;
    ticks++;
}

void Intel4004::SRC(UCommand command)
{
    //Get the 3 bits for registerpair
    uint4_t registerPair = (command.nibble.opa >> 1) & 0b0111;
    uint8_t valueOfRegisterPair = getRegisterPair(ERegister(registerPair));
    RAM->setCurrentChip(ERAMChip(valueOfRegisterPair >> 6));
    RAM->setCurrentAddress(valueOfRegisterPair & 0b00111111);
    ROM->setCurrentChip(EROMChip(valueOfRegisterPair >> 4));
    ticks++;
}

void Intel4004::FIN(UCommand command) //ROM-only
{
    //Get the 3 bits for registerpair
    uint4_t designatedRegisterPair = (command.nibble.opa >> 1) & 0b0111;
    uint8_t valueOfRegisterPair0 = getRegisterPair(ERegister(Pair_R1_R0));
    UBankedAddress address = UBankedAddress(PC.banked.bank, valueOfRegisterPair0);
    uint8_t value = ROM->read(address); 
    registers[designatedRegisterPair] = value >> 4;  
    registers[designatedRegisterPair + 1] = value & 0b00001111; 
    ticks = ticks + 2;
}

void Intel4004::CLB()
{
    accumulator = 0;
    carryFlag = false;
    ticks++;
}

void Intel4004::CLC()
{
    carryFlag = false;
    ticks++;
}

void Intel4004::CMC()
{
    carryFlag = !carryFlag;
    ticks++;
}

void Intel4004::STC()
{
    carryFlag = true;
    ticks++;
}

void Intel4004::CMA()
{
    //XOR
    accumulator ^= 0b1111;
    ticks++;
}

void Intel4004::IAC()
{
    accumulator++;
    carryFlag = accumulator >> 4;
    //reset bits 4-7
    accumulator &= ~(0b11110000);
    ticks++;
}

void Intel4004::DAC()
{
    accumulator--;
    carryFlag = !(accumulator >> 4);
    //reset bits 4-7
    accumulator &= ~(0b11110000);
    ticks++;
}

void Intel4004::RAL()
{
    bool tempCarryFlag = carryFlag;
    carryFlag = accumulator & 0b1000;
    accumulator = accumulator << 1;
    accumulator = accumulator + tempCarryFlag;
    ticks++;
}

void Intel4004::RAR()
{
    
}



//Two Word Machine Instruction

void Intel4004::JUN(UCommand byte1, UCommand byte2)
{
    PC.banked.bank = byte1.nibble.opa;
    PC.banked.address = byte2.data;
    ticks = ticks + 2;
}

void Intel4004::JMS(UCommand byte1, UCommand byte2)
{
    UBankedAddress returnAddress = PC.inc();
    stack->push(returnAddress);
    PC.banked.bank = byte1.nibble.opa;
    PC.banked.address = byte2.data;
    ticks = ticks + 2;
}

void Intel4004::JCN(UCommand byte1, UCommand byte2)
{
    
}

void Intel4004::ISZ(UCommand byte1, UCommand byte2)
{
    
}

void Intel4004::FIM(UCommand byte1, UCommand byte2)
{
    
}