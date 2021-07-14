/*
	Authors:
	- Henry Schuler
    - Thomas Staudacher
*/
#ifndef _4001_h_
#define _4001_h_
// Include local header files
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\inc\MCS4BaseClasses.h"
#elif __unix__
	#include "../inc/MCS4BaseClasses.h"
#endif

// Declaring namespaces
using namespace std;


class Intel4001 : public Intel4001Base {
public:
    enum {
        ROM_CELLS_EACH_CHIP = 256,
        MAX_NUMBER_OF_ROM_CHIPS = 16
    };
    
    /**
     * Constructor for ROM memory
     * @param installedBanks Installed banks (Default all 16 banks)
     */
    Intel4001(const uint16_t installedBanks = 0xFFFF);
    
	/**
     * Destructor cleans up memory
     */
    virtual ~Intel4001();
    
	/**
     * Reset intern registers (data cells to 0x00, ports to 0x0)
     */
    virtual void reset();
    
	/**
     * Which banks are currently installed
     * @return Bits of installed banks
     */
    virtual uint16_t getEnabledBank() const;
    
	/**
     * Read program data (type binary)
     * @param path Source file
     */
    virtual void writeFromBinaryFile(const char * const path);
    
	/**
     * Read program data (type Intel HEX)
     * @param path Source file
     */
    virtual void writeFromIntelHexFile(const char * const path);
    
	/**
     * Read program data (type bytes)
     * @param data Data source/array
     * @param count Amount of bytes to write
     * @return Amount of written bytes
     */
    virtual int writeFrom(uint8_t *data, const int count);
    
	/**
     * Does the local address exist? (12bit).
     * if not, return false
     * @param address Linear address without bank
     * @return <c>true</c> if addressable, else <c>false</c>
     */
    virtual bool isLinAdrAccessable(const uint16_t address) const;
    
	/**
     * Read one byte from ROM-memory
     * @param address ROM-address
     * @return Byte
     */
    virtual uint8_t read(const UBankedAddress address) const;
    
	/**
     * Read nibble from ROM-port
	 * @param chip Chip
     * @param value Port-value
     */
    virtual uint4_t readFromPort(const EROMChip chip) const;
    
	/**
     * Write nibble to ROM-port
	 * @param chip Chip
     * @param value Port-value to write
	 * @return <c>true</c> if successful, else <c>false</c>
     */
    virtual bool writeToPort(const EROMChip chip, const uint4_t value);

    // Own functions

    /**
     * Set current chip
     * @param chip Chip 
     */
    virtual void setCurrentChip(const EROMChip chip);

    /**
     * Return currently selected chip
     * @return Chip
     */
    virtual EROMChip getCurrentChip() const;

    /**
     * Read nibble from ROM-port (based on currentChip)
     * @param value Port-value
     */
    virtual uint4_t readPort() const;
    
    /**
     * Write nibble to ROM-port (based on currentChip)
     * @param value Port-value
	 * @return <c>true</c> if successful, else <c>false</c>
     */
    virtual bool writePort(const uint4_t value);

protected:
    /**
     * Erase memory in not installed chips
     */
    virtual void clearROMWhoIsNotInstalled();

    /**
     * Currently installed/activated/available banks
     */
    const uint16_t installedBanks;
    
	/**
     * ROM memory (includes not installed banks)
     */
    uint8_t *ROM;
    
	/**
     * Is ROM-bank available (linear)
     */
    bool *INSTALLEDROM;

    /**
     * Currently selected chip
     */
    EROMChip currentChip;
    
	/**
     * Port memory (includes not installed banks)
     */
    uint4_t *PORTS;
    
	/**
     * Maximal amount of ROM memory positions that can exist
     */
    static const size_t ROM_MEMORY_SIZE;
};

#endif // _4001_h_
