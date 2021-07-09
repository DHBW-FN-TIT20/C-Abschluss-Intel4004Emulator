/*
	Autoren:
	- Henry Schuler
*/
// Include local header files
#include "4002.h"

// Include gloabl header files
#include <cstring>

// Declaring namespaces
using namespace std;


Intel4002::Intel4002(const uint32_t installedChips) : currentBank(BANK0), currentChip(CHIP0), currentNibbleAddress(0), RAM(nullptr), RAMStatus(nullptr), RAMPort(nullptr), INSTALLEDRAM(nullptr) {
    // Initialize RAM, RAMStatus, RAMPort, INSTALLEDRAM
    RAM = new uint4_t***[MAX_NUMBER_OF_BANKS]();
    RAMStatus = new uint4_t***[MAX_NUMBER_OF_BANKS]();
    RAMPort = new uint4_t*[MAX_NUMBER_OF_BANKS]();
    INSTALLEDRAM = new bool*[MAX_NUMBER_OF_BANKS]();
    uint32_t chips = installedChips;

    for (int i = 0; i < MAX_NUMBER_OF_BANKS; i++) {
        RAM[i] = new uint4_t**[MAX_NUMBER_OF_RAM_CHIPS]();
        RAMStatus[i] = new uint4_t**[MAX_NUMBER_OF_RAM_CHIPS]();
        RAMPort[i] = new uint4_t[MAX_NUMBER_OF_RAM_CHIPS];
        INSTALLEDRAM[i] = new bool[MAX_NUMBER_OF_RAM_CHIPS];

        for (int j = 0; j < MAX_NUMBER_OF_RAM_CHIPS; j++, chips >>= 1) {
            RAM[i][j] = new uint4_t*[MAX_NUMBER_OF_RAM_REGISTERS];
            RAMStatus[i][j] = new uint4_t*[MAX_NUMBER_OF_RAM_REGISTERS];

            INSTALLEDRAM[i][j] = chips & 1;

            for (int k = 0; k < MAX_NUMBER_OF_RAM_REGISTERS; k++) {
                RAM[i][j][k] = new uint4_t[RAM_CELLS_EACH_REGISTER];
                RAMStatus[i][j][k] = new uint4_t[STATUS_CELLS_EACH_REGISTER];
            }
        }
    }

    reset();
}

Intel4002::~Intel4002() {
    // Delete RAM, RAMStatus, RAMPort, INSTALLEDRAM
    for (int i = 0; i < MAX_NUMBER_OF_BANKS; i ++) {
        for (int j = 0; j < MAX_NUMBER_OF_RAM_CHIPS; j++) {
            for (int k = 0; k < MAX_NUMBER_OF_RAM_REGISTERS; k++) {
                delete[] RAM[i][j][k];
                delete[] RAMStatus[i][j][k];
            }
            delete[] RAM[i][j];
            delete[] RAMStatus[i][j];
        }
        delete[] RAM[i];
        delete[] RAMStatus[i];
        delete[] RAMPort[i];
        delete[] INSTALLEDRAM[i];
    }
    delete[] RAM;
    delete[] RAMStatus;
    delete[] RAMPort;
    delete[] INSTALLEDRAM;
}

void Intel4002::reset() {
    currentBank = BANK0;
    currentChip = CHIP0;
    currentRegister = REG0;
    currentNibbleAddress = 0;

    for (int i = 0; i < MAX_NUMBER_OF_BANKS; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_RAM_CHIPS; j++) {
            for (int k = 0; k < MAX_NUMBER_OF_RAM_REGISTERS; k++) {
                memset(RAM[i][j][k], 0, RAM_CELLS_EACH_REGISTER);
                memset(RAMStatus[i][j][k], 0, STATUS_CELLS_EACH_REGISTER);
            }
        }
        memset(RAMPort[i], 0, MAX_NUMBER_OF_RAM_CHIPS);
    }
}

bool Intel4002::isRAMAdrAccessable(const ERAMBank bank, const ERAMChip chip) const {
    return INSTALLEDRAM[bank][chip];
}

uint4_t Intel4002::readRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const {
    if (isRAMAdrAccessable(bank, chip)) {
        return RAM[bank][chip][ramregister][(nibbleaddress & 0b1111)];
    }
    return 0;
}

bool Intel4002::writeRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value) {
    if (isRAMAdrAccessable(bank, chip)) {
        RAM[bank][chip][ramregister][(nibbleaddress & 0b1111)] = value;
        return true;
    }
    return false;
}

bool Intel4002::isStatusAdrAccessable(const ERAMBank bank, const ERAMChip chip) const {
    return INSTALLEDRAM[bank][chip];
}

uint4_t Intel4002::readStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const {
    if (isStatusAdrAccessable(bank, chip) && nibbleaddress <= 0b11) {
        return RAMStatus[bank][chip][ramregister][(nibbleaddress & 0b11)];
    }
    return 0;
}

bool Intel4002::writeStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value) {
    if (isStatusAdrAccessable(bank, chip) && nibbleaddress <= 0b11) {
        RAMStatus[bank][chip][ramregister][(nibbleaddress & 0b11)] = value;
        return true;
    }
    return false;
}

uint4_t Intel4002::readFromPortBuffer(const ERAMBank bank, const ERAMChip chip) const {
    if (isRAMAdrAccessable(bank, chip)) {
        return RAMPort[bank][chip];
    }
    return 0;
}

// Our functions

uint4_t Intel4002::readRAM() {
    return readRAMNibble(currentBank, currentChip, currentRegister, currentNibbleAddress);
}

bool Intel4002::writeRAM(const uint4_t value) {
    return writeRAMNibble(currentBank, currentChip, currentRegister, currentNibbleAddress, value);
}

uint4_t Intel4002::readStatus(const int address) {
    return readStatusNibble(currentBank, currentChip, currentRegister, (address & 0b11));
}

bool Intel4002::writeStatus(const int address, const uint4_t value) {
    return writeStatusNibble(currentBank, currentChip, currentRegister, (address & 0b11), value);
}

uint4_t Intel4002::readPortBurffer() {
    return readFromPortBuffer(currentBank, currentChip);
}

bool Intel4002::writePortBuffer(uint4_t value) {
    if (isRAMAdrAccessable(currentBank, currentChip)) {
        RAMPort[currentBank][currentChip] = value;
        return true;
    }
    return false;
}

void Intel4002::setCurrentBank(const ERAMBank bank) {
    if (BANK0 <= bank && bank <= BANK7) {
        currentBank = bank;
    }
}

void Intel4002::setCurrentChip(const ERAMChip chip) {
    if (CHIP0 <= chip && chip <= CHIP3) {
        currentChip = chip;
    }
}

void Intel4002::setCurrentRegister(const ERAMRegister reg) {
    currentRegister = reg;
}

void Intel4002::setCurrentNibbleAddress(const int address) {
    currentNibbleAddress = (address & 0b1111);
}
