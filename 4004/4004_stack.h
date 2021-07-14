/*
	Authors:
	- Henry Schuler
	- Thomas Staudacher
*/
#ifndef _4004_STACK_H_
#define _4004_STACK_H_
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


/**
 * Stack handling for Intel4004 processor.
 * Ring-stack (meaning addresses will be overwritten)
 * Overwriting if more than 3 addresses are saved/pushed (without read)
 */
class Intel4004Stack : public Intel4004StackBase {
public:
	/** 
	 * Constructor 
	 */
	Intel4004Stack();

	/**
	 * Copy-constructor
	 * @param other Object to be copied
	 */
	Intel4004Stack(const Intel4004Stack &other);

	/**
	 * Destructor 
	 */
	virtual ~Intel4004Stack();

	enum {
        STACKSIZE = 3	//!< Maximale size of ring-stack
    };

    /**
     * Direction of action
     */
    typedef enum {
        PUSH,	//!< Write
        POP		//!< Read
    } EDirection;

	/**
	 * Write UBankedAddress to stack
	 * @param address Address
	 */
	virtual void push(const UBankedAddress address);

	/**
	 * Read UBankedAddress from stack
	 * @return Address
	 */
	virtual UBankedAddress pop();

	/**
	 * Reset stack to default
	 */
	virtual void reset();

	/**
	 * Return current stack-position
	 * @return Stack-position
	 */
	virtual int getCurrentStackPosition() const;

	/**
	 * Counts amount of written addresses
	 * @return amount
	 */
	virtual int getCount() const;

	/**
	 * Checks if stack overflow occurred (more write than read)
	 * @return <c>true</c> if overflow, else <c>false</c>
	 */
	virtual bool isOverflow() const;

	/**
	 * Checks if stack underflow occurred (more read than write)
	 * @return <c>true</c> if underflow, else <c>false</c>
	 */
	virtual bool isUnderflow() const;

	/**
	 * Copy of current stack content
	 * @param ptr Pointer to stack copy (UBankedAddress array with STACKSIZE)
	 * @return Pointer to stack copy
	 */
	UBankedAddress* getCopyOfStack(UBankedAddress *const ptr) const;

protected:
	/** 
	 * Is called if error occurred (overflow/underflow)
	 */
	virtual void WarningCondition(const EDirection direction);

private:
	/** 
	 * Position of stack-pointer
	 */
	int position;
	
	/** 
	 * Amount of saved addresses 
	 */
	int count;
	
	/** 
	 * Stack memory
	 */
	UBankedAddress *stack;
};
#endif // _4004_STACK_H_
