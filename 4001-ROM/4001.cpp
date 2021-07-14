/*
	Authors:
	- Henry Schuler
    - Thomas Staudacher
*/
// Include local header files
#include "4001.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\inc\intelhex.h"
#elif __unix__
	#include "../inc/intelhex.h"
#endif

// Include gloabl header files
#include <cstring>
#include <fstream>

// Declaring namespaces
using namespace std;


Intel4001::Intel4001(const uint16_t installedBanks) : installedBanks(installedBanks), currentChip(ROMCHIP0), ROM(nullptr), INSTALLEDROM(nullptr), PORTS(nullptr) {
    ROM = new uint8_t[ROM_MEMORY_SIZE];
    INSTALLEDROM = new bool[MAX_NUMBER_OF_ROM_CHIPS];
    PORTS = new uint4_t[MAX_NUMBER_OF_ROM_CHIPS];

    // Install available ROM Chips (copy installedBanks to bool-array)
    {
        uint16_t banks = {installedBanks};
        for(auto chip = 0; chip < MAX_NUMBER_OF_ROM_CHIPS; ++chip, banks >>= 1)
            INSTALLEDROM[chip] = banks & 1;
    }
}

Intel4001::~Intel4001() {
    delete [] ROM;
    delete [] INSTALLEDROM;
    delete [] PORTS;
}

void Intel4001::reset() {
    memset(ROM, 0, ROM_MEMORY_SIZE);
    memset(PORTS, 0, MAX_NUMBER_OF_ROM_CHIPS);
    currentChip = ROMCHIP0;
}

uint16_t Intel4001::getEnabledBank() const {
    return installedBanks;
}

void Intel4001::writeFromBinaryFile(const char * const path) {
    ifstream is (path, ifstream::binary);
    if(is.is_open()) {
        is.read((char *)ROM, ROM_MEMORY_SIZE);
        // Delete written data in not installed Chips
        clearROMWhoIsNotInstalled();
        is.close();
    }
}

void Intel4001::writeFromIntelHexFile(const char * const path) {
    if(!readHexFile(path, ROM, ROM_MEMORY_SIZE))
    {
        // Error case
    }
    // Delete written data in not installed Chips
    else clearROMWhoIsNotInstalled();
}

int Intel4001::writeFrom(uint8_t *data, const int count) {
    if ((count < 1) || (count > static_cast<const int>(ROM_MEMORY_SIZE)))
        return 0;
    else {
        memcpy(ROM, data, count);
        // Delete written data in not installed Chips
        clearROMWhoIsNotInstalled();
        return count;
    }
}

bool Intel4001::isLinAdrAccessable(const uint16_t address) const {
    UBankedAddress banked = {address};
    return INSTALLEDROM[banked.banked.bank];
}

uint8_t Intel4001::read(const UBankedAddress address) const {
    return ROM[address.raw & 0x0FFF];
}

uint4_t Intel4001::readFromPort(const EROMChip chip) const {
    if(INSTALLEDROM[chip]) {
        return PORTS[chip];
    }
    else return 0;
}

bool Intel4001::writeToPort(const EROMChip chip, const uint4_t value) {
    if(INSTALLEDROM[chip]) {
        PORTS[chip] = value;
        return true;
    }
    return false;
}

void Intel4001::clearROMWhoIsNotInstalled() {
    for(auto chip = 0; chip < MAX_NUMBER_OF_ROM_CHIPS; chip++)
        if(!INSTALLEDROM[chip]) memset(ROM+chip*ROM_CELLS_EACH_CHIP,0,ROM_CELLS_EACH_CHIP);
}

const size_t Intel4001::ROM_MEMORY_SIZE = { MAX_NUMBER_OF_ROM_CHIPS * ROM_CELLS_EACH_CHIP };

// Own functions

void Intel4001::setCurrentChip(const EROMChip chip) {
    if (isLinAdrAccessable(UBankedAddress(chip, 0).raw)) {
        currentChip = chip;
    }
}

EROMChip Intel4001::getCurrentChip() const {
    return currentChip;
}

uint4_t Intel4001::readPort() const {
    return readFromPort(currentChip);
}

bool Intel4001::writePort(const uint4_t value) {
    return writeToPort(currentChip, value);
}
