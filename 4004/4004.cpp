/*
* Autoren:
* - Mnemonics: David Felder, Florian Herkommer
* - Ausimplementierung Intel4004: Lea Silberzahn
*/
// Include local header files
#include "4004.h"

// Include gloabl header files
#include <cstring>

// Declaring namespaces
using namespace std;


Intel4004::Intel4004(const uint16_t installed_ROM_Chips, const uint32_t installed_RAM_Chips)
{
    registers = new uint4_t[MAX_NUMBER_OF_REGISTERS]();
    ROM = new Intel4001(installed_ROM_Chips);
    RAM = new Intel4002(installed_RAM_Chips);
    stack = new Intel4004Stack();
}

Intel4004::~Intel4004()
{
    delete[] registers;
    delete[] ROM;
    delete[] RAM;
    delete[] stack;
}

void Intel4004::reset()
{
    carryFlag = 0;
	testPin = 0;
	accumulator = 0;
	ticks = 0;
	PC = 0;
	memset(registers, 0, MAX_NUMBER_OF_REGISTERS);
	ROM->reset();
	RAM->reset();
	stack->reset();

    // "A RESET causes DATA RAM BANK 0 to be selected" - MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf, p.3-49
}

bool Intel4004::getCarry() const
{
    return carryFlag;
}

uint4_t Intel4004::getAccumulator() const
{
    return accumulator;
}

UBankedAddress Intel4004::getPC() const
{
    return PC;
}

uint4_t Intel4004::getRegister(const ERegister reg)
{
    return registers[reg];
}

uint8_t Intel4004::getRegisterPair(const ERegister reg)
{
    uint8_t value = 0;
    value |= registers[reg];
    value = value << 4;
    value |= registers[reg+1];
    return value;
}

Intel4001Base* Intel4004::getPtrToROM()
{
    return ROM;
}

Intel4002Base* Intel4004::getPtrToRAM()
{
    return RAM;
}

Intel4004StackBase* Intel4004::getPtrToStack()
{
    return stack;
}

uint64_t Intel4004::getTicks() const
{
    return ticks;
}

void Intel4004::resetTicks()
{
    ticks = 0;
}

bool Intel4004::getTestPin() const
{
    return testPin;
}

void Intel4004::setTestPin(const bool value)
{
    testPin = value;
}

void Intel4004::nextCommand()
{
    //read command from rom
    UCommand command;
    UCommand secondWord;
    command.data = ROM->read(PC);
    PC.inc();
    switch (command.nibble.opr)
    {
    case 0x0:
        NOP();
        break;
    case 0x1:
        secondWord.data = ROM->read(PC);
        PC.inc();
        JCN(command, secondWord);
        break;
    case 0x2:
        //if opa ist not a even number
        if(command.nibble.opa % 2)
        {
            SRC(command);
        }
        else
        {
            secondWord.data = ROM->read(PC);
            PC.inc();
            FIM(command, secondWord);
        }
        break;
    case 0x3:
        //if opa ist not a even number
        if (command.nibble.opa & 1)
        {
            JIN(command);
        }
        else
        {
            FIN(command);
        }
        break;
    case 0x4:
        secondWord.data = ROM->read(PC);
        PC.inc();
        JUN(command, secondWord);
        break;
    case 0x5:
        secondWord.data = ROM->read(PC);
        PC.inc();
        JMS(command, secondWord);
    case 0x6:
        INC(command);
        break;
    case 0x7:
        secondWord.data = ROM->read(PC);
        PC.inc();
        ISZ(command, secondWord);
        break;
    case 0x8:
        ADD(command);
        break;
    case 0x9:
        SUB(command);
        break;
    case 0xA:
        LD(command);
        break;
    case 0xB:
        XCH(command);
        break;
    case 0xC:
        BBL(command);
        break;
    case 0xD:
        LDM(command);
    case 0xE:
        switch (command.nibble.opa)
        {
        case 0x0:
            WRM();
            break;
        case 0x1:
            WMP();
            break;
        case 0x2:
            WRR();
            break;
        case 0x3:
            WPM();
            break;
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
            WRn(command);
            break;
        case 0x8:
            SBM();
            break;
        case 0x9:
            RDM();
            break;
        case 0xA:
            RDR();
            break;
        case 0xB:
            ADM();
            break;
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
            RDn(command);
            break;                
        default:
            break;
        }
        break;
    case 0xF:
    switch (command.nibble.opa)
        {
        case 0x0:
            CLB();
            break;
        case 0x1:
            CLC();
            break;
        case 0x2:
            IAC();
            break;
        case 0x3:
            CMC();
            break;
        case 0x4:
            CMA();
            break;
        case 0x5:
            RAL();
            break;
        case 0x6:
            RAR();
            break;
        case 0x7:
            TCC();
            break;
        case 0x8:
            DAC();
            break;
        case 0x9:
            TCS();
            break;
        case 0xA:
            STC();
            break;
        case 0xB:
            DAA();
            break;
        case 0xC:
            KBP();
            break;
        case 0xD:
            DCL();
            break;               
        default:
            break;
        }
    break;
    default:
        break;
    }
}

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
    RAM->setCurrentRegister(ERAMRegister((valueOfRegisterPair >> 4) & 0b11));
    RAM->setCurrentNibbleAddress(valueOfRegisterPair & 0b1111);
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
    registers[designatedRegisterPair*2] = value >> 4;  
    registers[designatedRegisterPair*2 + 1] = value & 0b00001111; 
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
    //reset bits 4-7
    accumulator &= ~(0b11110000);
    ticks++;
}

void Intel4004::RAR()
{
    bool tempCarryFlag = carryFlag;
    carryFlag = accumulator & 1;
    accumulator = accumulator >> 1;
    accumulator = accumulator + (tempCarryFlag * 0b1000);
    //reset bits 4-7
    accumulator &= ~(0b11110000);
    ticks++;
}

void Intel4004::TCC()
{
    accumulator = 0;
    accumulator = carryFlag;
    carryFlag = false;
    ticks++;
}

void Intel4004::DAA()
{
    if ((accumulator > 9) or (carryFlag)) {
        accumulator += 6;
        if (accumulator < 6) {
            carryFlag = true;
        }
    }
    ticks++;
}

void Intel4004::TCS()
{
    if (carryFlag) {
        accumulator = 0b1010;
    } else {
        accumulator = 0b1001;
    }
    carryFlag = false;
    ticks++;
}

void Intel4004::KBP()
{
    int count = 0;
    uint4_t n = accumulator;
    while (n) {
        n &= (n - 1);
        count++;
        }
    if (count > 1) {
        accumulator = 0b1111;
    } else if (accumulator & 0b0001) {
        accumulator = 0b0001;
    } else if (accumulator & 0b0010) {
        accumulator = 0b0010;
    } else if (accumulator & 0b0100) {
        accumulator = 0b0011;
    } else if (accumulator & 0b1000) {
        accumulator = 0b0100;
    } else {
        accumulator = 0b0000;
    }
    ticks++;
}

void Intel4004::DCL()
{
    RAM->setCurrentBank(ERAMBank(accumulator & 0b0111));
    //uint4_t n = (accumulator & 0b0111);
    // if (n == 0b0000) {
    //     RAM->setCurrentBank(BANK0);
    // } else if (n == 0b0001) {
    //     RAM->setCurrentBank(BANK1);
    // } else if (n == 0b0010) {
    //     RAM->setCurrentBank(BANK2);
    // } else if (n == 0b0011) {
    //     RAM->setCurrentBank(BANK3);
    // } else if (n == 0b0100) {
    //     RAM->setCurrentBank(BANK4);
    // } else if (n == 0b0101) {
    //     RAM->setCurrentBank(BANK5);
    // } else if (n == 0b0110) {
    //     RAM->setCurrentBank(BANK6);
    // } else if (n == 0b0111) {
    //     RAM->setCurrentBank(BANK7);
    // }
    ticks++;
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
    uint4_t jumpCondition = byte1.nibble.opa;
    bool jumpBool = false;
    uint4_t caseAccuAndTest = 0;
    uint4_t caseCarry = 1;

    if (jumpCondition & 0b1000) {
        caseAccuAndTest = 1;
        caseCarry = 0;
    }

    if (jumpCondition & 0b0100) {
        if (accumulator == caseAccuAndTest) {
            jumpBool = true;
        }
    }
    if (jumpCondition & 0b0010) {
        if (carryFlag == caseCarry) {
            jumpBool = true;
        }
    }
    if (jumpCondition & 0b0001) {
        if (testPin == caseAccuAndTest) {
            jumpBool = true;
        }
    }

    if (jumpBool) {
        PC.banked.address = byte2.data;
    }
    ticks = ticks + 2;
}

void Intel4004::ISZ(UCommand byte1, UCommand byte2)
{
    registers[byte1.nibble.opa] = (0b1111 & (registers[byte1.nibble.opa] + 1));
    if (registers[byte1.nibble.opa] != 0){
        PC.banked.address = byte2.data;
    }
    ticks = ticks + 2;
}

void Intel4004::FIM(UCommand byte1, UCommand byte2)
{
    // todo vgl. mit FIN wegen ">> 1" und "*2"
    // 14.6. changed byte1 to byte2 (+2 lines)
    uint4_t designatedRegister = ((byte1.nibble.opa >> 1) & 0b0111) * 2;
    registers[designatedRegister] = byte2.nibble.opr;
    registers[designatedRegister + 1] = byte2.nibble.opa;
    ticks = ticks + 2;
}

//RAM Instructions
void Intel4004::RDM() {
    accumulator = RAM->readRAM();
    ticks++;
}

void Intel4004::RDn(UCommand command) {
    accumulator = RAM->readStatus((command.nibble.opa & 0b11));
    ticks++;
}

void Intel4004::RDR() {
    accumulator = ROM->readPort();
    ticks++;
}

void Intel4004::WRM() {
    RAM->writeRAM(accumulator);
    ticks++;
}

void Intel4004::WRn(UCommand command) {
    RAM->writeStatus((command.nibble.opa & 0b11), accumulator);
    ticks++;
}

void Intel4004::WPM() {
    // No function because irrelevant???
    ticks++;
}

void Intel4004::WRR() {
    ROM->writePort(accumulator);
    ticks++;
}

void Intel4004::WMP() {
    RAM->writePortBuffer(accumulator);
    ticks++;
}

void Intel4004::ADM() {
    uint8_t result = accumulator + RAM->readRAM() + carryFlag;
    accumulator = result & 0b1111;
    carryFlag = (result >> 4) & 0b1;
    ticks++;
}

void Intel4004::SBM() {
    uint8_t result = accumulator + (RAM->readRAM() ^ 0b1111) + !carryFlag;
    accumulator = result & 0b1111;
    carryFlag = !((result >> 4) & 0b1);
    ticks++;
}

Intel4004Base* get4004Instance(const uint16_t installed_ROM_Chips, const uint32_t installed_RAM_Chips) {
	return new Intel4004(installed_ROM_Chips, installed_RAM_Chips);
}
