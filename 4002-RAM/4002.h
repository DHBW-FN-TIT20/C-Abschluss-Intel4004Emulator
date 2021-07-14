/*
	Author:
	- Henry Schuler
*/
#ifndef _4002_h_
#define _4002_h_
// Include local header files
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\inc\MCS4BaseClasses.h"
#elif __unix__
	#include "../inc/MCS4BaseClasses.h"
#endif

// Include global header files
#include <cstdint>

// Declaring namespaces
using namespace std;


class Intel4002 : public Intel4002Base {
public:
	enum {
        RAM_CELLS_EACH_REGISTER = 16,
		STATUS_CELLS_EACH_REGISTER = 4,
		MAX_NUMBER_OF_RAM_REGISTERS = 4,
        MAX_NUMBER_OF_RAM_CHIPS = 4,
		MAX_NUMBER_OF_BANKS = 8
    };

	/**
	 * Constructor
	 */
	Intel4002(const uint32_t installedChips = 0xFFFFFFFF);
	
	/**
	 * Destructor
	 */
	virtual ~Intel4002();
	
	/**
	 * Reset intern registers and values (except installedChips)
	 */
	virtual void reset();
	
	/**
	 * Does the RAM-address exist.
	 * @param bank Bank
	 * @param chip Chip
	 * @param address RAM-memory address
	 * @return <c>true</c> if addressable, else <c>false</c>
	 */
	virtual bool isRAMAdrAccessable(const ERAMBank bank, const ERAMChip chip) const;
	
	/**
	 * Read one nibble from RAM-memory
	 * @param bank Bank
	 * @param chip Chip
	 * @param address RAM-memory address
	 * @return RAM-memory value
	 */
	virtual uint4_t readRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const;
	
	/**
	 * Write one nibble to RAM-memory
	 * @param bank Bank
	 * @param chip Chip
	 * @param address RAM-memory address
	 * @param value RAM-memory value
	 * @return <c>true</c> if successful, else <c>false</c>
	 */
	virtual bool writeRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value);
	
	/**
	 * Does the RAM-status-address exist.
	 * @param bank Bank
	 * @param chip Chip
	 * @param address RAM-memory address
	 * @return <c>true</c> if addressable, else <c>false</c>
	 */
	virtual bool isStatusAdrAccessable(const ERAMBank bank, const ERAMChip chip) const;
	
	/**
	 * Read one nibble from RAM-status-memory
	 * @param bank Bank
	 * @param chip Chip
	 * @param address RAM-status-memory address
	 * @return RAM-status-memory value
	 */
	virtual uint4_t readStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const;
	
	/**
	 * Write one nibble to RAM-status-memory
	 * @param bank Bank
	 * @param chip Chip
	 * @param address RAM-status-memory address
	 * @param value RAM-status-memory value
	 * @return <c>true</c> if successful, else <c>false</c>
	 */
	virtual bool writeStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value);
	
	/**
	 * Read one nibble from RAM-port
	 * @param bank Bank
	 * @param chip Chip
	 * @return Port-value
	 */
	virtual uint4_t readFromPortBuffer(const ERAMBank bank, const ERAMChip chip) const;
	
	// Our functions

	/**
	 * Read one nibble from RAM-memory (based on currently selected RAM-Module)
	 * @return Memory-value
	 */
	virtual uint4_t readRAM();
	
	/**
	 * Write one nibble to RAM-memory (based on currently selected RAM-Module)
	 * @param value Memory-value
	 * @return <c>true</c> if successful, else <c>false</c>
	 */
	virtual bool writeRAM(const uint4_t value);
	
	/**
	 * Read one nibble from RAM-status-memory (based on currently selected RAM-Module)
	 * @param address Status-address
	 * @return Status-value
	 */
	virtual uint4_t readStatus(const int address);
	
	/**
	 * Write one nibble to RAM-status-memory (based on currently selected RAM-Module)
	 * @param address Status-address
	 * @param value Status-value
	 * @return <c>true</c> if successful, else <c>false</c>
	 */
	virtual bool writeStatus(const int address, const uint4_t value);
	
	/**
	 * Read one nibble from RAM-port (based on currently selected RAM-Module)
	 * @return Port-value
	 */
	virtual uint4_t readPortBuffer();
	
	/**
	 * Write one nibble to ROM-port (based on currently selected RAM-Module)
	 * @param value Port-value
	 * @return <c>true</c> if successful, else <c>false</c>
	 */
	virtual bool writePortBuffer(uint4_t value);
	
	/**
	 * Set currently selected bank
	 * @param bank Bank
	 */
	virtual void setCurrentBank(const ERAMBank bank);
	
	/**
	 * Set currently selected chip
	 * @param chip Chip
	 */
	virtual void setCurrentChip(const ERAMChip chip);
	
	/**
	 * Set currently selected register
	 * @param reg Register
	 */
	virtual void setCurrentRegister(const ERAMRegister reg);
	
	/**
	 * Set currently selected address
	 * @param address Address
	 */
	virtual void setCurrentNibbleAddress(const int address);

private:
	/**
     * Active bank
     */
	ERAMBank currentBank;
	
	/**
     * Active chip
     */
	ERAMChip currentChip;
	
	/**
     * Active register
     */
	ERAMRegister currentRegister;
	
	/**
     * Active address
     */
	int currentNibbleAddress;
	
	/**
     * RAM memory
     */
	uint4_t ****RAM;
	
	/**
     * RAM status memory
     */
	uint4_t ****RAMStatus;
	
	/**
     * RAM port memory
     */
	uint4_t **RAMPort;
	
	/**
     * Installed RAM-chips
     */
	bool **INSTALLEDRAM;
};
#endif // _4002_h_
