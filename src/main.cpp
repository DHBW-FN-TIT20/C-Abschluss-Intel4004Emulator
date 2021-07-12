/*
	Autoren:
	- Henry Schuler
	- David Felder
	- Lea Silberzahn
	- Florian Herkommer
*/
// Include local header files
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include "..\4004\4004.h"
#elif __unix__
    #include "../4004/4004.h"
#endif

// Include global header files
#include <iostream>
#include <iomanip>

// Declaring namespaces
using namespace std;

// Declaring functions
void functionIntel4004();
bool functionPrintProcessorState(Intel4004Base *processor);

// MAIN
int main() {
    functionIntel4004();
    return 0;
}

// Functions
void functionIntel4004() {
    // Instantiate an Intel4004 processor
    Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };
    Intel4004Base *secondProcessor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };


    // Access RAM Module
    Intel4002Base *RAM = processor->getPtrToRAM();


    // Access ROM Module
    Intel4001Base *ROM = processor->getPtrToROM();


    // Write to ROM
    // Array containing Commands (FIM_0 0xFF, NOP)
    uint8_t source[] = { 0x50, 0xFF, 0x00 };
    processor->getPtrToROM()->writeFrom(source, sizeof(source));
    // IntelHex file
    processor->getPtrToROM()->writeFromIntelHexFile("hexFilePath");
    // Binary file
    processor->getPtrToROM()->writeFromBinaryFile("binaryFilePath");


    // Perform next command operation
    processor->nextCommand();
    
    // View current state of processor
    functionPrintProcessorState(processor);
}


bool functionPrintProcessorState(Intel4004Base *processor) {
    cout << "---- Intel4004 Emulation ----" << endl << endl;
    cout << "Intel4004 CPU:" << endl;
    cout << setw(10) << "PC " << hex << setw(3) << setfill('0') << (int) processor->getPC().raw << dec << setfill(' ') << endl;
    UBankedAddress stackCopy[3];
    processor->getPtrToStack()->getCopyOfStack(stackCopy);
    cout << setw(10) << "Level 1 " << hex << setw(3) << setfill('0') << (int) stackCopy[(processor->getPtrToStack()->getCurrentStackPosition() + 2) % 3].raw << dec << setfill(' ') << endl;
    cout << setw(10) << "Level 2 " << hex << setw(3) << setfill('0') << (int) stackCopy[processor->getPtrToStack()->getCurrentStackPosition() % 3].raw << dec << setfill(' ') << endl;
    cout << setw(10) << "Level 3 " << hex << setw(3) << setfill('0') << (int) stackCopy[(processor->getPtrToStack()->getCurrentStackPosition() + 1) % 3].raw << dec << setfill(' ') << endl;
    cout << endl;
    cout << "Registers:" << endl;
    cout << "R0R1 " << hex << (int) processor->getRegister(R0) << " " << (int) processor->getRegister(R1) << dec << endl;
    cout << "R2R3 " << hex << (int) processor->getRegister(R2) << " " << (int) processor->getRegister(R3) << dec << endl;
    cout << "R4R5 " << hex << (int) processor->getRegister(R4) << " " << (int) processor->getRegister(R5) << dec << endl;
    cout << "R6R7 " << hex << (int) processor->getRegister(R6) << " " << (int) processor->getRegister(R7) << dec << endl;
    cout << "R8R9 " << hex << (int) processor->getRegister(R8) << " " << (int) processor->getRegister(R9) << dec << endl;
    cout << "RARB " << hex << (int) processor->getRegister(R10) << " " << (int) processor->getRegister(R11) << dec << endl;
    cout << "RCRD " << hex << (int) processor->getRegister(R12) << " " << (int) processor->getRegister(R13) << dec << endl;
    cout << "RERF " << hex << (int) processor->getRegister(R14) << " " << (int) processor->getRegister(R15) << dec << endl;
    cout << endl;
    cout << "Accumulator " << setw(1) << setfill('0') << hex << (int) processor->getAccumulator() << dec << endl;
    cout << "Carry " << setw(1) << setfill('0') << hex << processor->getCarry() << "  Test " << setw(1) << setfill('0') << processor->getTestPin() << dec << endl;
    cout << endl;
    cout << endl;
    cout << "Intel4002 RAM:" << endl;
    cout << endl;
    cout << "Bank 0, Chip 0:" << endl;
    cout << endl;
    cout << setw(10) << setfill(' ') << " " << "0 1 2 3 4 5 6 7 8 9 A B C D E F" << setw(4) << " " << "0 1 2 3" << endl;
    for (int j = 0; j < 4; j++) {
        cout << setw(8) << "Register" << j << " ";
        for (int i = 0; i < 16; i++) {
            cout << hex << (int) processor->getPtrToRAM()->readRAMNibble(BANK0, CHIP0, (ERAMRegister) j, i) << " " << dec;
        }
        cout << setw(3) << " ";
        for (int i = 0; i < 4; i++) {
            cout << hex << (int) processor->getPtrToRAM()->readStatusNibble(BANK0, CHIP0, (ERAMRegister) j, i) << " " << dec;
        }
        cout << endl;
    }
    cout << endl;
	
	return true;
}
