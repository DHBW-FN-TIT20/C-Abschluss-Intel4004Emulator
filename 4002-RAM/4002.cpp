// Include local header files
#include "4002.h"

// Include gloabl header files
#include <cstring>

// Declaring namespaces
using namespace std;

Intel4002::Intel4002(const uint32_t installedChips) : currentBank(BANK0), currentChip(CHIP0), currentAddress(0), RAM(nullptr), RAMStatus(nullptr), RAMPort(nullptr), INSTALLEDRAM(nullptr) {
    // Initialize RAM, RAMStatus, RAMPort, INSTALLEDRAM
    RAM = new uint4_t**[MAX_NUMBER_OF_BANKS]();
    RAMStatus = new uint4_t**[MAX_NUMBER_OF_BANKS]();
    RAMPort = new uint4_t*[MAX_NUMBER_OF_BANKS]();
    INSTALLEDRAM = new bool*[MAX_NUMBER_OF_BANKS]();
    uint16_t chips = installedChips;

    for (int i = 0; i < MAX_NUMBER_OF_BANKS; i++) {
        RAM[i] = new uint4_t*[MAX_NUMBER_OF_RAM_CHIPS]();
        RAMStatus[i] = new uint4_t*[MAX_NUMBER_OF_RAM_CHIPS]();
        RAMPort[i] = new uint4_t[MAX_NUMBER_OF_RAM_CHIPS];
        INSTALLEDRAM[i] = new bool[MAX_NUMBER_OF_RAM_CHIPS];

        for (int j = 0; j < MAX_NUMBER_OF_RAM_CHIPS; j++, chips >>= 1) {
            RAM[i][j] = new uint4_t[RAM_CELLS_EACH_CHIP];
            RAMStatus[i][j] = new uint4_t[STATUS_CELLS_EACH_CHIP];

            INSTALLEDRAM[i][j] = chips & 1;
        }
    }

    reset();
}

Intel4002::~Intel4002() {
    // Delete RAM, RAMStatus, RAMPort, INSTALLEDRAM
    for (int i = 0; i < MAX_NUMBER_OF_BANKS; i ++) {
        for (int j = 0; j < MAX_NUMBER_OF_RAM_CHIPS; j++) {
            delete[] RAM[i][j];
            delete[] RAMStatus[i][j];
        }
        delete[] RAM[i];
        delete[] RAMStatus[i];
        delete[] RAMPort[i];
    }
    delete[] RAM;
    delete[] RAMStatus;
    delete[] RAMPort;
    delete[] INSTALLEDRAM;
}

void Intel4002::reset() {
    currentBank = BANK0;
    currentChip = CHIP0;
    currentAddress = 0;

    for (int i = 0; i < MAX_NUMBER_OF_BANKS; i++) {
        for (int j = 0; j < MAX_NUMBER_OF_RAM_CHIPS; j++) {
            memset(RAM[i][j], 0, RAM_CELLS_EACH_CHIP);
            memset(RAMStatus[i][j], 0, STATUS_CELLS_EACH_CHIP);
        }
        memset(RAMPort[i], 0, MAX_NUMBER_OF_RAM_CHIPS);
    }
}

bool Intel4002::isRAMAdrAccessable(const ERAMBank bank, const ERAMChip chip, const int address) const {
    return (INSTALLEDRAM[bank][chip] && 0 <= address && address <= RAM_CELLS_EACH_CHIP);
}

uint4_t Intel4002::readRAMNibble(const ERAMBank bank, const ERAMChip chip, const int address) const {
    if (isRAMAdrAccessable(bank, chip, address)) {
        return RAM[bank][chip][address];
    }
    return 0;
}

bool Intel4002::writeRAMNibble(const ERAMBank bank, const ERAMChip chip, const int address, const uint4_t value) const {
    if (isRAMAdrAccessable(bank, chip, address)) {
        RAM[bank][chip][address] = value;
        return true;
    }
    return false;
}

bool Intel4002::isStatusAdrAccessable(const ERAMBank bank, const ERAMChip chip, const int address) const {
    return (INSTALLEDRAM[bank][chip] && 0b00 <= (address >> 4) && (address >> 4) <= 0b11 && 0b0000 <= (address & 0b1111) && (address & 0b1111) <= 0b0011);
}

uint4_t Intel4002::readStatusNibble(const ERAMBank bank, const ERAMChip chip, const int address) const {
    if (isStatusAdrAccessable(bank, chip, address)) {
        return RAMStatus[bank][chip][(address >> 4) * 4 + (address & 0b1111)];
    }
    return 0;
}

bool Intel4002::writeStatusNibble(const ERAMBank bank, const ERAMChip chip, const int address, const uint4_t value) const {
    if (isStatusAdrAccessable(bank, chip, address)) {
        RAMStatus[bank][chip][(address >> 4) * 4 + (address & 0b1111)] = value;
        return true;
    }
    return false;
}

uint4_t Intel4002::readFromPortBuffer(const ERAMBank bank, const ERAMChip chip) const {
    if (isRAMAdrAccessable(bank, chip, 0)) {
        return RAMPort[bank][chip];
    }
    return 0;
}

// Our functions

bool Intel4002::writePortBuffer(const ERAMBank bank, const ERAMChip chip, uint4_t value) {
    if (isRAMAdrAccessable(bank, chip, 0)) {
        RAMPort[bank][chip] = value;
        return true;
    }
    return false;
}

void Intel4002::setCurrentBank(const ERAMBank bank) {
    if (BANK0 <= bank && bank <= BANK7) {
        currentBank = bank;
    }
}

ERAMBank Intel4002::getCurrentBank() const {
    return currentBank;
}

void Intel4002::setCurrentChip(const ERAMChip chip) {
    if (CHIP0 <= chip && chip <= CHIP3) {
        currentChip = chip;
    }
}

ERAMChip Intel4002::getCurrentChip() const {
    return currentChip;
}

void Intel4002::setCurrentAddress(const int address) {
    if (0 <= address && address <= RAM_CELLS_EACH_CHIP) {
        currentAddress = address;
    }
}

int Intel4002::getCurrentAddress() const {
    return currentAddress;
}