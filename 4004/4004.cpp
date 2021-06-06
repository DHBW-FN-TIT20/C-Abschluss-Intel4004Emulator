// Include local header files
#include "4004.h"

// Include gloabl header files

// Declaring namespaces
using namespace std;


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
}

void Intel4004::CLC()
{
    carryFlag = false;
}

void Intel4004::CMC()
{
    carryFlag = !carryFlag;
}

void Intel4004::STC()
{
    carryFlag = true;
}

void Intel4004::CMA()
{
    //XOR
    accumulator ^= 0b1111;
}




