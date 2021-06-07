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
        MAX_NUMBER_OF_REGISTERS = 16
    };
	/**
	 * Konstruktor
	 */
	Intel4004();
	/**
	 * Destruktor
	 */
	virtual ~Intel4004();
	/**
	 * Setzt den Prozessor zurück
	 */
	virtual void reset();
	/**
	 * Gibt den Wert des Übertrags aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Übertrag
	 */
	virtual bool getCarry() const;
	/**
	 * Gibt den Wert des Akkumulators aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Akkumulator
	 */
	virtual uint4_t getAccumulator() const;
	/**
	 * Gibt die aktuelle Adresse der Ablaufsteuerung aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Adresse der Ablaufsteuerung
	 */
	virtual UBankedAddress getPC() const;
	/**
	 * Dient zum auslesen eines Registers (Register 0..15).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registernummer
	 * @return Nibble
	 */
	virtual uint4_t getRegister(const ERegister reg);
	/**
	 * Dient zum auslesen eines Registerspaars (Register R1R0 ... R15R14).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registerpaar Nummer
	 * @return Byte
	 */
	virtual uint8_t getRegisterPair(const ERegister reg);
	/**
	 * Gibt den ROM Handle zurück.
	 * @return ROM Handle
	 */
	virtual Intel4001Base* getPtrToROM();
	/**
	 * Gibt den RAM Handle zurück.
	 * @return RAM Handle
	 */
	virtual Intel4002Base* getPtrToRAM();
	/**
	 * Gibt den Stack Handle zurück.
	 * @return Stack Handle
	 */
	virtual Intel4004StackBase* getPtrToStack();
	/**
	 * Gibt die Anzahl der Ticks (Subzyklen) zurück die bisher gemessen wurden.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return Anzahl Ticks
	 */
	virtual uint64_t getTicks() const;
	/**
	 * Setzt die Ticks zurück (Subzyklen)
	 */
	virtual void resetTicks();
	/** Gibt den Pin zurück (Hardwareschnittstelle).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual bool getTestPin() const;
	/**
	 * Setzt den Pin (Hardwareschnittstelle)
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @param value <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual void setTestPin(const bool value);
	/** Ruft die Programmablaufschnittstelle auf. Über diese Schnittstelle können die Befehle Step für Step abgearbeitet werden. */
	virtual void nextCommand();

private:
	bool carryFlag;
	bool testPin;
	uint4_t accumulator;
	uint64_t ticks;
	UBankedAddress PC;
	uint4_t *registers;
	Intel4001 *ROM;
	Intel4002 *RAM;
	Intel4004Stack *stack;
	
	/** Intel4004 operation functions
	 *	PC zuerst erhöhen, dann Funktion aufrufen!!
	 * 	Bei two-word-commands liest nextCommand() beide Bytes ein und übergibt diese an die jeweilige Funtion
	 */

	/******* One word machine instruction ********************/
	/**
	 * No Operation
	 */
	void NOP();
	/**
	 * Load data to Accumulator
	 */
	void LDM(UCommand command);
	/**
	 * Load index register to Accumulator
	 */ 
	void LD(UCommand command);
	/**
	 * Exchange index register and accumulator
	 */ 
	void XCH(UCommand command);
	/**
	 * Add index register to accumulator with carry
	 */ 
	void ADD(UCommand command);
	/**
	 * Subtract index register from accumulator with borrow
	 */ 
	void SUB(UCommand command);
	/**
	 * Increment index register
	 */ 
	void INC(UCommand command);
	/**
	 * Branch back and load data to the accumulator
	 */ 
	void BBL(UCommand command);
	/**
	 * Jump indirect
	 */ 
	void JIN(UCommand command);
	/**
	 * Send register control
	 */ 
	void SRC(UCommand command);
	/**
	 * Fetch indirect from ROM
	 */ 
	void FIN(UCommand command);

	/******************Accumulator Group Instructions **********/

	/**
	 * Clear both
	 */
	void CLB();
	/**
	 * Clear carry
	 */
	void CLC();
	/**
	 * Complement carry
	 */
	void CMC();
	/**
	 * Set carry
	 */
	void STC();
	/**
	 * Complement Accumulator
	 */
	void CMA();
	/**
	 * Increment accumulator
	 */
	void IAC();
	/**
	 * decrement accumulator
	 */
	void DAC();
	/**
	 * Rotate left
	 */
	void RAL();
	/**
	 * Rotate right
	 */
	void RAR();

};
#endif // _4004_h_
