// Include local header files
#include "4004.h"

// Include gloabl header files

// Declaring namespaces
using namespace std;

class Intelpoc : public virtual Intel4004 {
public: 
    Intel4004(){}

    ~Intel4004() override {}

    void reset() override {}

    bool getCarry() const override {
        return  
    }

    uint4_t getAccumulator() const override {
        return accumulator;
    }

    UBankedAddress getPC() const override {}

    uint4_t getRegister(const ERegister reg) override {}
    uint8_t getRegisterPair(const ERegister reg) override {}
    Intel4001Base* getPtrToROM() override {
        return *ROM;
    }

    Intel4002Base* getPtrToRAM() override {
        return *RAM;
    }

    Intel4004StackBase* getPtrToStack() override {
        return *stack;
    }

    uint64_t getTicks() const override {}
    void resetTicks() override {}
    bool getTestPin() const override {
        return testPin;
    }

    void setTestPin(const bool value) override {
        testPin = value;
    }
    
    void nextCommand() override {}
};