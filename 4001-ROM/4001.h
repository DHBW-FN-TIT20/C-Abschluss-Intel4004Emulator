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
     * Ctor um den ROM Speicher zu erzeugen
     * @param installed_banks Installierte B�nke (Default alle 16 B�nke)
     */
    Intel4001(const uint16_t installed_banks = 0xFFFF);
    
	/**
     * Destruktor r�umt den Speicher auf
     */
    virtual ~Intel4001();
    
	/**
     * Setzt die internen Register zur�ck (Datenzellen auf 0x00, Ports auch auf 0)
     */
    virtual void reset();
    
	/**
     * Welche B�nke sind in diesem System verbaut
     * @return Bits der eingeschalteten B�nke
     */
    virtual uint16_t getEnabledBank() const;
    
	/**
     * Liest das Programm ein (Typ bin�r)
     * @param path Quelldatei
     */
    virtual void writeFromBinaryFile(const char * const path);
    
	/**
     * Liest das Programm ein (Typ Intel HEX)
     * @param path Quelldatei
     */
    virtual void writeFromIntelHexFile(const char * const path);
    
	/**
     * Liest das Programm ein (Typ Bytes)
     * @param data Datenquelle
     * @param count Anzahl Bytes die geschrieben werden
     * @return Anzahl
     */
    virtual int writeFrom(uint8_t *data, const int count);
    
	/**
     * Ist die lokale Adresse vorhanden (gibt es diese Adresse 12bit).
     * falls nicht wird false zur�ckgegeben
     * @param address Lineare Adresse ohne Bankangabe
     * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
     */
    virtual bool isLinAdrAccessable(const uint16_t address) const;
    
	/**
     * Liest ein Byte aus dem Speicher
     * @param address Adresse im Speicher
     * @return Byte
     */
    virtual uint8_t read(const UBankedAddress address) const;
    
	/**
     * Liest Nibble aus Portschnittstelle
	 * @param chip Chip
     * @param value Wert
     */
    virtual uint4_t readFromPort(const EROMChip chip) const;
    
	/**
     * Schreibe Nibble auf Portschnittstelle
	 * @param chip Chip
     * @param value Wert
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
     */
    virtual bool writeToPort(const EROMChip chip, const uint4_t value);

    // Own functions

    /**
     * Setzt den aktuellen Chip
     * @param chip Chip 
     */
    virtual void setCurrentChip(const EROMChip chip);

    /**
     * Liefert den aktuell ausgewählten Chip zurück
     * @return Chip
     */
    virtual EROMChip getCurrentChip() const;

    /**
     * Liest Nibble aus Portschnittstelle
     * @param value Wert
     */
    virtual uint4_t readPort() const;
    
    /**
     * Schreibe Nibble auf Portschnittstelle
     * @param value Wert
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
     */
    virtual bool writePort(const uint4_t value);

protected:
    /**
     * L�schte alle Speicherbereiche die nicht installiert sind
     */
    virtual void clearROMWhoIsNotInstalled();

    /**
     * Aktivierte B�nke
     */
    const uint16_t installed_banks;
    
	/**
     * ROM Inhalt (auch nicht installierte B�nke)
     */
    uint8_t *ROM;
    
	/**
     * Ist ROM installiert (linear)
     */
    bool *INSTALLEDROM;

    /**
     * Aktuell ausgewählter Chip
     */
    EROMChip currentChip;
    
	/**
     * Port Inhalt (auch nicht installierte B�nke)
     */
    uint4_t *PORTS;
    
	/**
     * Maximale Anzahl von ROM Speicherstellen die das System �berhaupt haben kann
     */
    static const size_t ROM_MEMORY_SIZE;
};

#endif // _4001_h_
