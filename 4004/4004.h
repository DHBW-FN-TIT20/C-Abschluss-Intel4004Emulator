/*
	Authors:
	- David Felder
	- Florian Herkommer
	- Henry Schuler
	- Lea Silberzahn
*/
#ifndef _4004_h_
#define _4004_h_
// Include local header files
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\inc\MCS4BaseClasses.h"
	#include "..\4001-ROM\4001.h"
	#include "..\4002-RAM\4002.h"
#elif __unix__
	#include "../inc/MCS4BaseClasses.h"
	#include "../4001-ROM/4001.h"
	#include "../4002-RAM/4002.h"
#endif
#include "4004_stack.h"

// Include global header files
#include <cstdint>

// Declaring namespaces
using namespace std;


class Intel4004 : public Intel4004Base {
public:
	enum {
        MAX_NUMBER_OF_REGISTERS = 16,
		TICKS_PER_CYCLE = 8
    };
	
	/**
	 * Constructor
	 */
	Intel4004(const uint16_t installed_ROM_Chips = 0xFFFF, const uint32_t installed_RAM_Chips = 0xFFFFFFFF);
	
	/**
	 * Destructor
	 */
	virtual ~Intel4004();
	
	/**
	 * Reset processor to default
	 */
	virtual void reset();
	
	/**
	 * Return carry flag
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf p.19
	 * @return Carry flag
	 */
	virtual bool getCarry() const;
	
	/**
	 * Return accumulator value
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf p.19
	 * @return Accumulator value
	 */
	virtual uint4_t getAccumulator() const;
	
	/**
	 * Return current program address (currently executed command position)
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf p.19
	 * @return Program address
	 */
	virtual UBankedAddress getPC() const;
	
	/**
	 * Read register content (register 0..15).
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf p.19 and MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.11
	 * @param reg Register
	 * @return Register content (nibble)
	 */
	virtual uint4_t getRegister(const ERegister reg);
	
	/**
	 * Read register pair content (register R1R0 ... R15R14).
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf p.19 and MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.11
	 * @param reg Register pair
	 * @return Register pair content (byte)
	 */
	virtual uint8_t getRegisterPair(const ERegister reg);
	
	/**
	 * Return pointer to ROM
	 * @return ROM pointer
	 */
	virtual Intel4001Base* getPtrToROM();
	
	/**
	 * Return pointer to RAM
	 * @return RAM pointer
	 */
	virtual Intel4002Base* getPtrToRAM();
	
	/**
	 * Return pointer to stack
	 * @return Stack pointer
	 */
	virtual Intel4004StackBase* getPtrToStack();
	
	/**
	 * Return amount of ticks since start of execution
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf p.6
	 * @return Amount ticks
	 */
	virtual uint64_t getTicks() const;
	
	/**
	 * Reset ticks
	 */
	virtual void resetTicks();
	
	/**
	 * Return test pin state
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf p.6
	 * @return <c>true</c> if set, else <c>false</c>
	 */
	virtual bool getTestPin() const;
	
	/**
	 * Set/reset test pin
	 * <br>Hint:</br> Take a look at studienarbeit-4004.pdf S.6
	 * @param value <c>true</c> if set, else reset <c>false</c>
	 */
	virtual void setTestPin(const bool value);
	
	/** 
	 * Execute next command in ROM. Iterate through program step by step.
	 */
	virtual void nextCommand();

private:
	/**
	 * Carry flag
	 */
	bool carryFlag;

	/**
	 * Test pin
	 */
	bool testPin;

	/**
	 * Accumulator (4bit)
	 */
	uint4_t accumulator;
	
	/**
	 * Tick counter
	 */
	uint64_t ticks;
	
	/**
	 * Program counter (stores address of executed command)
	 */
	UBankedAddress PC;
	
	/**
	 * Register memory
	 */
	uint4_t *registers;

	/**
	 * ROM instance
	 */
	Intel4001 *ROM;

	/**
	 * RAM instance
	 */
	Intel4002 *RAM;

	/**
	 * Stack instance
	 */
	Intel4004Stack *stack;
	

	/******* One-Word-Instructions *****************************/
	/**
	 * No Operation
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-48
	 */
	void NOP();
	
	/**
	 * Load data to Accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-37
	 * @param UCommand command
	 */
	void LDM(UCommand command);
	
	/**
	 * Load index register to Accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-24
	 * @param UCommand command
	 */ 
	void LD(UCommand command);
	
	/**
	 * Exchange index register and accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-25
	 * @param UCommand command
	 */ 
	void XCH(UCommand command);
	
	/**
	 * Add index register to accumulator with carry
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-21
	 * @param UCommand command
	 */ 
	void ADD(UCommand command);
	
	/**
	 * Subtract index register from accumulator with borrow
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-22
	 * @param UCommand command
	 */ 
	void SUB(UCommand command);
	
	/**
	 * Increment index register
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-17
	 * @param UCommand command
	 */ 
	void INC(UCommand command);
	
	/**
	 * Branch back and load data to the accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-46
	 * @param UCommand command
	 */ 
	void BBL(UCommand command);
	
	/**
	 * Jump indirect
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-40
	 * @param UCommand command
	 */ 
	void JIN(UCommand command);
	
	/**
	 * Send register control
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-50
	 * @param UCommand command
	 */ 
	void SRC(UCommand command);
	
	/**
	 * Fetch indirect from ROM
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-18
	 * @param UCommand command
	 */ 
	void FIN(UCommand command);

	
	/******* Accumulator-Group-Instructions ********************/
	/**
	 * Clear both
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-27
	 */
	void CLB();
	
	/**
	 * Clear carry
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-27
	 */
	void CLC();
	
	/**
	 * Complement carry
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-29
	 */
	void CMC();
	
	/**
	 * Set carry
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-34
	 */
	void STC();
	
	/**
	 * Complement Accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-29
	 */
	void CMA();
	
	/**
	 * Increment accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-28
	 */
	void IAC();
	
	/**
	 * Decrement accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-32
	 */
	void DAC();
	
	/**
	 * Rotate left
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-30
	 */
	void RAL();
	
	/**
	 * Rotate right
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-31
	 */
	void RAR();
	
	/**
	 * Transmit carry and clear
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-32
	 */
	void TCC();
	
	/**
	 * Decimal adjust accumulator
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-34
	 */
	void DAA();
	
	/**
	 * Transfer carry subtract
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-33
	 */
	void TCS();
	
	/**
	 * Keyboard process
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-35
	 */
	void KBP();
	
	/**
	 * Designate command line
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-48
	 */
	void DCL();

	
	/******* Two-Word-Instructions *****************************/
	/**
	 * Jump unconditional
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-38
	 * @param UCommand firstCommand
	 * @param UCommand secondCommand
	 */
	void JUN(UCommand byte1, UCommand byte2);
	
	/**
	 * Jump to Subroutine
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-45
	 * @param UCommand firstCommand
	 * @param UCommand secondCommand
	 */
	void JMS(UCommand byte1, UCommand byte2);
	
	/**
	 * Jump conditional
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-41
	 * @param UCommand firstCommand
	 * @param UCommand secondCommand
	 */
	void JCN(UCommand byte1, UCommand byte2);
	
	/**
	 * Increment index register skip if zero
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-43
	 * @param UCommand firstCommand
	 * @param UCommand secondCommand
	 */
	void ISZ(UCommand byte1, UCommand byte2);
	
	/**
	 * Fetched immediate from ROM
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-36
	 * @param UCommand firstCommand
	 * @param UCommand secondCommand
	 */
	void FIM(UCommand byte1, UCommand byte2);

	
	/******* Input-Output-Instructions *************************/
	/**
	 * Read RAM character
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-54
	 */
	void RDM();
	
	/**
	 * Read RAM status character 0-3
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-54
	 */
	void RDn(UCommand command);
	
	/**
	 * Read ROM port
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-55
	 * @param UCommand command
	 */
	void RDR();
	
	/**
	 * Write accumulator into RAM character
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-56
	 */
	void WRM();
	
	/**
	 * Write accumulator into RAM status character 0-3
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-57
	 * @param UCommand command
	 */
	void WRn(UCommand command);
	
	/**
	 * Write Program RAM
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-62
	 * <br>Hint:</br> This function has no implementation because Intel4008/Intel4009 are missing
	 */
	void WPM();
	
	/**
	 * Write ROM port
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-59
	 */
	void WRR();
	
	/**
	 * Write memory port
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-58
	 */
	void WMP();
	
	/**
	 * Add from memory with carry
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-60
	 */
	void ADM();
	
	/**
	 * Subtract from memory with borrow
	 * <br>Hint:</br> Take a look at MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf p.3-61
	 */
	void SBM();
};
#endif // _4004_h_
