// Include local header files
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\4002-RAM\4002.h"
    #include "..\4004\4004.h"
#elif __unix__
	#include "../4002-RAM/4002.h"
    #include "../4004/4004.h"
#endif

// Include global header files
#include <iostream>
#include <iomanip>

// Declaring namespaces
using namespace std;

// Declaring functions
void functionTestIntel4002();
void functionTestIntel4004();

// MAIN
int main() {
    functionTestIntel4004();
    return 0;
}

// Functions
void functionTestIntel4002() {
    // Intel4002 test(0b1011001110101111);

    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         cout << "Bank: " << i << " Chip: " << j << " : " << test.isRAMAdrAccessable((ERAMBank) i, (ERAMChip) j) << endl;
    //     }
    // }
    
    // cout << "Bank: 0 Chip: 0 Register: 1 Adresse: 15 : " << test.isRAMAdrAccessable(BANK0, CHIP0, REG1, 15) << endl;

    // test.writeRAMNibble(BANK0, CHIP0, 0, 0xF);
    // test.writeRAMNibble(BANK0, CHIP0, 3, 0x5);

    // for (int i = 0; i < 64; i++) {
    //     cout << hex << (int) test.readRAMNibble(BANK0, CHIP0, i) << " " << dec;
    // }

    // cout << endl;

    // cout << (0b110001 >> 4) << " " << test.isStatusAdrAccessable(BANK0, CHIP0, 0b110001) << endl;

    // test.writeStatusNibble(BANK0, CHIP0, 0, 0xF);
    // test.writeStatusNibble(BANK0, CHIP0, 0b010010, 0xF);

    // cout << hex << (int) test.readStatusNibble(BANK0, CHIP0, 0b110001) << dec << endl;

    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         cout << hex << (int) test.readStatusNibble(BANK0, CHIP0, (i << 4) + j) << " " << dec;
    //     }
    // }

    // cout << endl;
    
    // test.writePortBuffer(BANK0, CHIP0, 0xF);
    // test.writePortBuffer(BANK2, CHIP1, 0xF);
    
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         cout << hex << (int) test.readFromPortBuffer((ERAMBank) i, (ERAMChip) j) << " " << dec;
    //     }
    // }

    // cout << endl;

    // test.setCurrentBank(BANK2);
    // test.setCurrentChip(CHIP1);
    // test.setCurrentAddress(0b110101);

    // cout << hex << "Bank: " << test.getCurrentBank() << " Chip: " << test.getCurrentChip() << " Address: " << test.getCurrentAddress() << endl << dec;
}

void functionTestIntel4004() {
    Intel4004 test();
    Intel4004Base *processor = { get4004Instance(0xFFFF, 0xFFFFFFFF) };
    processor->getPtrToROM()->writeFromIntelHexFile(".\\..\\Assembler-Examples\\P1.hex");
    // for (int i = 0; i < 1000; i++) {
    //     processor->nextCommand();
    // }
    while(processor->getTicks() < 390 ){
        processor->nextCommand();
    }

    uint4_t value = processor->getPtrToRAM()->readRAMNibble(BANK0,CHIP0, REG3, 15);
    cout << (int)value << endl;
    cout << (int)processor->getTicks() << endl;
}

// g++ main.cpp ..\inc\intelhex.c ..\4001-ROM\4001.cpp ..\4002-RAM\4002.cpp ..\4004\4004.cpp ..\4004\4004_stack.cpp