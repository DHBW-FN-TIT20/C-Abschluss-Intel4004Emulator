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
        RAM_CELLS_EACH_CHIP = 256,
        MAX_NUMBER_OF_RAM_CHIPS = 4,
		MAX_NUMBER_OF_BANKS = 8
    };
	/**
	 * Konstruktor
	 */
	Intel4002() {
	}
	/**
	 * Destruktor
	 */
	virtual ~Intel4002() {
	}
	/**
	 * Setzt die internen Register zurück zurück
	 */
	virtual void reset();
	/**
	 * Ist die RAM Adresse vorhanden.
	 * Falls nicht wird false zurückgegeben
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isRAMAdrAccessable(const ERAMBank bank, const ERAMChip chip, const int address) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return Wert
	 */
	virtual uint4_t readRAMNibble(const ERAMBank bank, const ERAMChip chip, const int address) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @param value Wert
	 * @return Ob an dieser Stelle schreibbar war
	 */
	virtual bool writeRAMNibble(const ERAMBank bank, const ERAMChip chip, const int address, const uint4_t value) const;
	/**
	 * Ist die Status Adresse vorhanden.
	 * Falls nicht wird false zurückgegeben
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
	 */
	virtual bool isStatusAdrAccessable(const ERAMBank bank, const ERAMChip chip, const int address) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @return Wert
	 */
	virtual uint4_t readStatusNibble(const ERAMBank bank, const ERAMChip chip, const int address) const;
	/**
	 * Ein Nibble an der derzeit angeforderten Adresse
	 * @param bank Bank
	 * @param chip Chip
	 * @param address Speicherzellenaddresse
	 * @param value Wert
	 * @return Ob an dieser Stelle schreibbar war
	 */
	virtual bool writeStatusNibble(const ERAMBank bank, const ERAMChip chip, const int address, const uint4_t value) const;
	/**
	 * Liest ein Nibble aus dem Ausgangspuffer
	 * @param bank Bank
	 * @param chip Chip
	 * @return Wert
	 */
	virtual uint4_t readFromPortBuffer(const ERAMBank bank, const ERAMChip chip) const;
	
	// Unsere besseren Funktionen

	/**
	 * Schreibt ein Nibble in den Ausgangspuffer
	 * @param bank Bank
	 * @param chip Chip
	 * @param value Wert
	 */
	virtual void writePortBuffer(const ERAMBank bank, const ERAMChip chip, uint4_t value);
	/**
	 * Setzt die aktuelle Bank
	 * @param bank Bank
	 */
	virtual void setCurrentBank(const ERAMBank bank);
	/**
	 * Gibt die aktuelle Bank zurück
	 * @return currentBank
	 */
	virtual ERAMBank getCurrentBank() const;
	/**
	 * Setzt den aktuellen Chip
	 * @param chip Chip
	 */
	virtual void setCurrentChip(const ERAMChip chip);
	/**
	 * Gibt den aktuellen Chip zurück
	 * @return currentChip
	 */
	virtual ERAMBank getCurrentChip() const;
	/**
	 * Setzt die aktuelle Adresse
	 * @param address Adresse
	 */
	virtual void setCurrentAddress(const int address);
	/**
	 * Gibt die aktuelle Adresse zurück
	 * @return currentAddress
	 */
	virtual ERAMBank getCurrentAddress() const;

private:
	ERAMBank currentBank;
	ERAMChip currentChip;
	int currentAddress;
	uint4_t ***RAM;
	uint4_t ***RAMStatus;
	uint4_t **RAMPort;

// int ***arr3D = new int**[X];
// for(int i =0; i<X; i++){
//    arr3D[i] = new int*[Y];
//    for(int j =0; j<Y; j++){
//        arr3D[i][j] = new int[Z];
//        for(int k = 0; k<Z;k++){
//           arr3D[i][j][k] = 0;
//        }
//    }
// }

// arr = new int **[height]();
//     for (i = 0; i < height; i++)
//     {
//         arr[i] = new int *[width]();
//         for (j = 0; j < width; j++)
//             arr[i][j] = new int [depth]();
//     }
// for (i = 0; i < rows; i++)
// {
//     for (j = 0; j < columns; j++)
//         delete[] arr[i][j];
//     delete[] arr[i];
// }
// delete[] arr;
};
#endif // _4002_h_
