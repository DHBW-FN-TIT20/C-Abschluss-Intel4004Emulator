#ifndef _MCS4BaseClasses_h_
#define _MCS4BaseClasses_h_

#include "400x_GlobalDefines.h"

#include<cstdint>

using namespace std;

/**
 * Stackverwaltung für den Intel4004 Prozessor.
 * Angelegt als Zirkularspeicher (d.h. es wird überschrieben)
 * wenn mehr wie drei Werte eingeschrieben worden sind und nicht
 * wieder ausgelesen.
 * <br>Hinweis:</br> Siehe MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 16ff
 */
class Intel4004StackBase {
public:
	/**
	 * Konstruktor
	 */
	Intel4004StackBase() {
	}
	/**
	 * Destruktor
	 */
	virtual ~Intel4004StackBase() {
	}

	/** Setzt den Stack zurück (auf den ersten Eintrag). */
	virtual void reset() = 0;

	/**
	 * Gibt die Aktulle Position im Stack aus
	 * @return Position
	 */
	virtual int getCurrentStackPosition() const = 0;

	/**
	 * Zahlt die Anzahl der eingeschriebenen Adressen (Wert 0..3)
	 * @return Anzahl
	 */
	virtual int getCount() const = 0;

	/**
	 * Gibt zurück ob der Stack übergelaufen ist (mehr Werte reingeschrieben wie reinpassen)
	 * @return <c>true</c> wenn Überlauf, sonst <c>false</c>
	 */
	virtual bool isOverflow() const = 0;

	/**
	 * Gibt zurück ob der Stack unterlauf ist (mehr Werte ausgelsen wie reingeschrieben)
	 * @return <c>true</c> wenn Unterlauf, sonst <c>false</c>
	 */
	virtual bool isUnderflow() const = 0;

	/**
	 * Kopie der Stackinhalte
	 * @param ptr Zeiger auf Kopie (Array der Größe STACKSIZE)
	 * @return Pointer auf Kopie
	 */
	virtual UBankedAddress* getCopyOfStack(UBankedAddress *const ptr) const = 0;
};

/** Basisklasse Intel 4001 ROM.
 * <br>Hinweis:</br> Siehe MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 12ff
 */
class Intel4001Base {
public:
	/**
	 * Konstruktor
	 */
	Intel4001Base() {
	}
	/**
	 * Destruktor
	 */
	virtual ~Intel4001Base() {
	}
	/**
	 * Setzt die internen Register zurück (Datenzellen auf 0x00, Ports auch auf 0)
	 */
	virtual void reset() = 0;
	/**
	 * Welche Bänke sind in diesem System verbaut
	 * @return Bits der eingeschalteten Bänke
	 */
	virtual uint16_t getEnabledBank() const = 0;
	/**
	 * Liest das Programm ein (Typ binär)
	 * @param path Quelldatei
	 */
	virtual void writeFromBinaryFile(const char *const path) = 0;
	/**
	 * Liest das Programm ein (Typ Intel HEX)
	 * @param path Quelldatei
	 */
	virtual void writeFromIntelHexFile(const char *const path) = 0;
	/**
	 * Liest das Programm ein (Typ Bytes)
	 * @param data Datenquelle
	 * @param count Anzahl Bytes die geschrieben werden
	 * @return Anzahl
	 */
	virtual int writeFrom(uint8_t *data, const int count) = 0;
	/**
	 * Ist die lokale Adresse vorhanden (gibt es diese Adresse 12bit).
	 * falls nicht wird false zurückgegeben
	 * @param address Lineare Adresse ohne Bankangabe
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isLinAdrAccessable(const uint16_t address) const = 0;
	/**
	 * Liest ein Byte aus dem Speicher
	 * @param address Adresse im Speicher
	 * @return Byte
	 */
	virtual uint8_t read(const UBankedAddress address) const = 0;
	/**
	 * Liest Nibble aus Portschnittstelle
	 * @param chip Chip
	 * @return value Wert
	 */
	virtual uint4_t readFromPort(const EROMChip chip) const = 0;
	/**
	 * Schreibe Nibble auf Portschnittstelle
	 * @param chip Chip
	 * @param value Wert
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool writeToPort(const EROMChip chip, const uint4_t value) = 0;
};

/** Basisklasse Intel 4002 RAM.
 * <br>Hinweis:</br> Siehe MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 14ff
 */
class Intel4002Base {
public:
	/**
	 * Konstruktor
	 */
	Intel4002Base() {
	}
	/**
	 * Destruktor
	 */
	virtual ~Intel4002Base() {
	}
	/**
	 * Setzt die internen Register zurück zurück
	 */
	virtual void reset() = 0;
	/**
	 * Ist die RAM Adresse vorhanden.
	 * Falls nicht wird false zurückgegeben
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isRAMAdrAccessable(const ERAMBank bank, const ERAMChip chip,
			const int address) const = 0;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return Wert
	 */
	virtual uint4_t readRAMNibble(const ERAMBank bank, const ERAMChip chip,
			const int address) const = 0;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @param value Wert
	 * @return Ob an dieser Stelle schreibbar war
	 */
	virtual bool writeRAMNibble(const ERAMBank bank, const ERAMChip chip,
			const int address, const uint4_t value) const = 0;
	/**
	 * Ist die Status Adresse vorhanden.
	 * Falls nicht wird false zurückgegeben
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isStatusAdrAccessable(const ERAMBank bank, const ERAMChip chip,
			const int address) const = 0;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return Wert
	 */
	virtual uint4_t readStatusNibble(const ERAMBank bank, const ERAMChip chip,
			const int address) const = 0;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @param value Wert
	 * @return Ob an dieser Stelle schreibbar war
	 */
	virtual bool writeStatusNibble(const ERAMBank bank, const ERAMChip chip,
			const int address, const uint4_t value) const = 0;
	/**
	 * Liest ein Nibble aus dem Ausgangspuffer
	 * @param bank Bank
	 * @param chip Chip
	 * @return Wert
	 */
	virtual uint4_t readFromPortBuffer(const ERAMBank bank,
			const ERAMChip chip) const = 0;
};

/** Basisklasse Intel 4004 Emulation */
class Intel4004Base {
public:
	/**
	 * Konstruktor
	 */
	Intel4004Base() {
	}
	/**
	 * Destruktor
	 */
	virtual ~Intel4004Base() {
	}
	/**
	 * Setzt den Prozessor zurück
	 */
	virtual void reset() = 0;
	/**
	 * Gibt den Wert des Übertrags aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Übertrag
	 */
	virtual bool getCarry() const = 0;
	/**
	 * Gibt den Wert des Akkumulators aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Akkumulator
	 */
	virtual uint4_t getAccumulator() const = 0;
	/**
	 * Gibt die aktuelle Adresse der Ablaufsteuerung aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Adresse der Ablaufsteuerung
	 */
	virtual UBankedAddress getPC() const = 0;
	/**
	 * Dient zum auslesen eines Registers (Register 0..15).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registernummer
	 * @return Nibble
	 */
	virtual uint4_t getRegister(const ERegister reg) = 0;
	/**
	 * Dient zum auslesen eines Registerspaars (Register R1R0 ... R15R14).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registerpaar Nummer
	 * @return Byte
	 */
	virtual uint8_t getRegisterPair(const ERegister reg) = 0;
	/**
	 * Gibt den ROM Handle zurück.
	 * @return ROM Handle
	 */
	virtual Intel4001Base* getPtrToROM() = 0;
	/**
	 * Gibt den RAM Handle zurück.
	 * @return RAM Handle
	 */
	virtual Intel4002Base* getPtrToRAM() = 0;
	/**
	 * Gibt den Stack Handle zurück.
	 * @return Stack Handle
	 */
	virtual Intel4004StackBase* getPtrToStack() = 0;
	/**
	 * Gibt die Anzahl der Ticks (Subzyklen) zurück die bisher gemessen wurden.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return Anzahl Ticks
	 */
	virtual uint64_t getTicks() const = 0;
	/**
	 * Setzt die Ticks zurück (Subzyklen)
	 */
	virtual void resetTicks() = 0;
	/** Gibt den Pin zurück (Hardwareschnittstelle).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual bool getTestPin() const = 0;
	/**
	 * Setzt den Pin (Hardwareschnittstelle)
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @param value <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual void setTestPin(const bool value) = 0;
	/** Ruft die Programmablaufschnittstelle auf. Über diese Schnittstelle können die Befehle Step für Step abgearbeitet werden. */
	virtual void nextCommand() = 0;

};
#endif
