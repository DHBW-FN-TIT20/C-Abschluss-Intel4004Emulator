/*
	Authors:
	- Henry Schuler
	- Thomas Staudacher
*/
// Include local header files
#include "4004_stack.h"

// Include global header files
#include <cstdint>
#include <cstring>

// Declaring namespaces
using namespace std;


Intel4004Stack::Intel4004Stack() : position(0), count(0), stack(nullptr) {
	stack = new UBankedAddress[STACKSIZE];
	memset(stack, 0, STACKSIZE * sizeof(UBankedAddress));
}

Intel4004Stack::Intel4004Stack(const Intel4004Stack &other) : Intel4004Stack() {
	position = other.position;
	count = other.count;
	other.getCopyOfStack(stack);
}

Intel4004Stack::~Intel4004Stack() {
	delete[] stack;
}

void Intel4004Stack::push(const UBankedAddress address) {
	if (count >= STACKSIZE) {
		WarningCondition(EDirection::PUSH);
	}
	stack[2] = stack[1];
	stack[1] = stack[0];
	stack[0] = address;

	position = (position + 1) % 3;
	++count;
}

UBankedAddress Intel4004Stack::pop() {
	if (count < 1) {
		WarningCondition(EDirection::POP);
	}

	auto ret = stack[0];
	// Popped address remains on stack at position 2
	stack[0] = stack[1];
	stack[1] = stack[2];
	stack[2] = ret;

	position = ((position - 1) + 3) % 3;
	--count;

	return ret;
}

void Intel4004Stack::reset() {
	position = count = 0;
	memset(stack, 0, STACKSIZE * sizeof(UBankedAddress));
}

int Intel4004Stack::getCurrentStackPosition() const {
	return count % 3;
}

int Intel4004Stack::getCount() const {
	if(count < 1) return 0;
	else if(count > STACKSIZE) return STACKSIZE;
	else return count;
}

bool Intel4004Stack::isOverflow() const {
	return count > STACKSIZE;
}

bool Intel4004Stack::isUnderflow() const {
	return count < 0;
}

UBankedAddress* Intel4004Stack::getCopyOfStack(UBankedAddress *const ptr) const {
	return static_cast<UBankedAddress*>(memcpy(ptr, stack, STACKSIZE * sizeof(UBankedAddress)));
}

void Intel4004Stack::WarningCondition(const EDirection) {
	// Is called at overflow/underflow
}
