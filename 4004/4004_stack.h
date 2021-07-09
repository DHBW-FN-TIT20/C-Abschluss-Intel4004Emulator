#ifndef _4004_STACK_H_
#define _4004_STACK_H_
// Include local header files
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\inc\MCS4BaseClasses.h"
#elif __unix__
	#include "../inc/MCS4BaseClasses.h"
#endif

// Include gloabel header files
#include <cstdint>

// Declaring namespaces
using namespace std;


/**
 * Stackverwaltung für den Intel4004 Prozessor.
 * Angelegt als Zirkularspeicher (d.h. es wird überschrieben)
 * wenn mehr wei drei Werte eingeschrieben worden sind und nicht
 * wieder ausgelesen.
 */
class Intel4004Stack : public Intel4004StackBase {
public:
	/** Konstruktor */
	Intel4004Stack();

	/**
	 * Copy-Konstruktor
	 * @param other Zu kopierendes Objekt
	 */
	Intel4004Stack(const Intel4004Stack &other);

	/** Destruktor */
	virtual ~Intel4004Stack();

	enum {
        STACKSIZE = 3	//!< Maximale Größe des Intel 4004 Stacks
    };

    /**
     * Wirkrichtung
     */
    typedef enum {
        PUSH,	//!< Hineinspeichern
        POP		//!< Herausholen
    } EDirection;

	/**
	 * Schreibt eine Adresse (Wert) in den Stack ein
	 * @param address Adresse
	 */
	virtual void push(const UBankedAddress address);

	/**
	 * Liest eine Adresse (Wert) aus dem Stack aus
	 * @return Adresse
	 */
	virtual UBankedAddress pop();

	/** Setzt den Stack zurück */
	virtual void reset();

	/**
	 * Gibt die Aktulle Position im Stack aus
	 * @return Position
	 */
	virtual int getCurrentStackPosition() const;

	/**
	 * Zahlt die Anzahl der eingeschriebenen Adressen (Werte)
	 * @return Anzahl
	 */
	virtual int getCount() const;

	/**
	 * Gibt zurück ob der Stack übergelaufen ist (mehr Werte reingeschrieben wie reinpassen)
	 * @return <c>true</c> wenn Überlauf, sonst <c>false</c>
	 */
	virtual bool isOverflow() const;

	/**
	 * Gibt zurück ob der Stack unterlauf ist (mehr Werte ausgelsen wie reingeschrieben)
	 * @return <c>true</c> wenn Unterlauf, sonst <c>false</c>
	 */
	virtual bool isUnderflow() const;

	/**
	 * Kopie der Stackinhalte
	 * @param ptr Zeiger auf Kopie (Array der Größe STACKSIZE)
	 * @return Pointer auf Kopie
	 */
	UBankedAddress* getCopyOfStack(UBankedAddress *const ptr) const;

protected:

	/** Wird aufgerufen wenn ein Fehler passiert */
	virtual void WarningCondition(const EDirection direction);
private:

	/** Position des Stackzeigers */
	int position;
	/** Zählt die Anzahl der eingeschriebenen Adressen (Werte) */
	int count;
	/** Stackspeicher */
	UBankedAddress *stack;
};
#endif // _4004_STACK_H_
