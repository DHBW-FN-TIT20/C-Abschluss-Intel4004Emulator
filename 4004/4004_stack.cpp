// Include local header files
#include "4004_stack.h"

// Include global header files
#include <cstdint>
#include <cstring>

// Declaring namespaces
using namespace std;

Intel4004Stack::Intel4004Stack() :
		position(0), count(0), stack(nullptr) {
	stack = new UBankedAddress[STACKSIZE];
	memset(stack, 0, STACKSIZE * sizeof(UBankedAddress));
}

Intel4004Stack::Intel4004Stack(const Intel4004Stack &other) :
		Intel4004Stack() {
	position = other.position;
	count = other.count;
	other.getCopyOfStack(stack);
}

Intel4004Stack::~Intel4004Stack() {
	delete[] stack;
}

void Intel4004Stack::push(const UBankedAddress address) {
	// if (count < 0) {
	// 	count = position = 0;
	// } else if (count >= STACKSIZE) {
	if (count >= STACKSIZE) {

	 	// ++count;
		WarningCondition(EDirection::PUSH);
	// 	return;
	}

	stack[2] = stack[1];
	stack[1] = stack[0];
	stack[0] = address;

	// ++position;
	position = (position + 1) % 3;
	++count;
}

UBankedAddress Intel4004Stack::pop() {
	if (count < 1) {
		// --count;
		WarningCondition(EDirection::POP);
		//return 0;
	}

	auto ret = stack[0];

	//Positionen korrigieren (noch nicht so schoen, geht mit verkette Elemente besser)
	stack[0] = stack[1];
	stack[1] = stack[2];
	stack[2] = ret;

	position = ((position - 1) + 3) % 3;
	// if (position > 0)
	// 	--position;

	--count;

	return ret;
}

void Intel4004Stack::reset() {
	position = count = 0;
	memset(stack, 0, STACKSIZE * sizeof(UBankedAddress));
}

int Intel4004Stack::getCurrentStackPosition() const {
	//return position;
	if(count < 1) return 0;
	else if(count > STACKSIZE) return STACKSIZE;
	else return count;
}

int Intel4004Stack::getCount() const {
	return count;
}

bool Intel4004Stack::isOverflow() const {
	return count >= STACKSIZE;
}

bool Intel4004Stack::isUnderflow() const {
	return count < 0;
}

UBankedAddress* Intel4004Stack::getCopyOfStack(
		UBankedAddress *const ptr) const {
	return static_cast<UBankedAddress*>(memcpy(ptr, stack,
			STACKSIZE * sizeof(UBankedAddress)));
}

void Intel4004Stack::WarningCondition(const EDirection) { /* Wird bei Unter/Überschreitungen aufgerufen */
}

/***************** Sektion UNITTEST ************************************************************************/
#ifdef _UNITTEST_

#define CATCH_CONFIG_FAST_COMPILE

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\inc\catch.hpp"
#elif __unix__
	#include "../inc/catch.hpp"
#endif

class MyStack: public Intel4004Stack {
	bool reported_overflow, reported_underflow;
public:
	bool getReportedOverflow() {
		auto ret = reported_overflow;
		reported_overflow = false;
		return ret;
	}
	bool getReportedUnderflow() {
		auto ret = reported_underflow;
		reported_underflow = false;
		return ret;
	}
protected:
	virtual void WarningCondition(const EDirection direction) {
		if (direction == EDirection::POP)
			reported_underflow = true;
		else
			reported_overflow = true;
	}
};

TEST_CASE("Stack") {
	SECTION("CopyConstructorStack") {
		MyStack stack;

		CHECK_FALSE(stack.getCount());
		CHECK_FALSE(stack.getCurrentStackPosition());

		//Beschreiben
		stack.push(1);
		CHECK(stack.getCount() == 1);
		CHECK(stack.getCurrentStackPosition() == 1);
		stack.push(2);
		CHECK(stack.getCount() == 2);
		CHECK(stack.getCurrentStackPosition() == 2);
		stack.push(3);
		CHECK(stack.getCount() == 3);
		CHECK(stack.getCurrentStackPosition() == 3);

		//Copyconstruktor
		MyStack copy(stack);

		//Auslesen
		CHECK(copy.getCount() == 3);
		CHECK(copy.getCurrentStackPosition() == 3);
		CHECK(copy.pop().raw == 3);
		CHECK(copy.getCount() == 2);
		CHECK(copy.getCurrentStackPosition() == 2);
		CHECK(copy.pop().raw == 2);
		CHECK(copy.getCount() == 1);
		CHECK(copy.getCurrentStackPosition() == 1);
		CHECK(copy.pop().raw == 1);
		CHECK_FALSE(copy.getCount());
		CHECK_FALSE(copy.getCurrentStackPosition());
	}

	SECTION("EnterValuesToStackNormalUse") {
		MyStack stack;

		CHECK_FALSE(stack.getCount());
		CHECK_FALSE(stack.getCurrentStackPosition());

		//Beschreiben
		stack.push(1);
		CHECK(stack.getCount() == 1);
		CHECK(stack.getCurrentStackPosition() == 1);
		stack.push(2);
		CHECK(stack.getCount() == 2);
		CHECK(stack.getCurrentStackPosition() == 2);
		stack.push(3);
		CHECK(stack.getCount() == 3);
		CHECK(stack.getCurrentStackPosition() == 3);
		//Auslesen
		CHECK(stack.pop().raw == 3);
		CHECK(stack.getCount() == 2);
		CHECK(stack.getCurrentStackPosition() == 2);
		CHECK(stack.pop().raw == 2);
		CHECK(stack.getCount() == 1);
		CHECK(stack.getCurrentStackPosition() == 1);
		CHECK(stack.pop().raw == 1);
		CHECK_FALSE(stack.getCount());
		CHECK_FALSE(stack.getCurrentStackPosition());
	}

	SECTION("EnterValuesToStack_UnderflowPushAgain") {
		MyStack stack;

		CHECK_FALSE(stack.getCount());
		CHECK_FALSE(stack.getCurrentStackPosition());

		//Underflow ausgelöst
		CHECK(stack.pop().raw == 0);
		CHECK(stack.getCount() == -1);
		CHECK(stack.getCurrentStackPosition() == 0);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK(stack.getReportedUnderflow());

		//Ein Wert wieder reinschreiben
		stack.push(1);
		CHECK(stack.getCount() == 1);
		CHECK(stack.getCurrentStackPosition() == 1);
	}

	SECTION("EnterValuesToStackMishMashNoOverflow") {
		MyStack stack;

		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());

		//Beschreiben
		stack.push(1);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.push(2);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		//Auslesen
		CHECK(stack.pop().raw == 2);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());

		//Beschreiben
		stack.push(3);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		//Auslesen
		CHECK(stack.pop().raw == 3);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		CHECK(stack.pop().raw == 1);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());

	}

	SECTION("EnterValuesToStackOverflowCallback") {
		MyStack stack;

		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());

		//Beschreiben
		stack.push(1);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.push(2);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.push(3);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.push(4);
		CHECK(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.push(5);
		CHECK(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.reset();
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
	}

	SECTION("EnterValuesToStackUnderflowCallback") {
		MyStack stack;

		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());

		//Beschreiben
		stack.push(1);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.push(2);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		stack.push(3);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());

		CHECK(stack.pop().raw == 3);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		CHECK(stack.pop().raw == 2);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		CHECK(stack.pop().raw == 1);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK_FALSE(stack.getReportedUnderflow());
		CHECK(stack.pop().raw == 0);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK(stack.getReportedUnderflow());
		CHECK(stack.pop().raw == 0);
		CHECK_FALSE(stack.getReportedOverflow());
		CHECK(stack.getReportedUnderflow());
	}
}
#endif //_UNITTEST_
