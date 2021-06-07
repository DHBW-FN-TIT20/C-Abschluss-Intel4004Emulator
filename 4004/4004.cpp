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
