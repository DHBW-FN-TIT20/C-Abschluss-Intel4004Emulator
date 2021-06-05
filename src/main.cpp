// Include local header files
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\4002-RAM\4002.h"
#elif __unix__
	#include "../4002-RAM/4002.h"
#endif

// Include global header files
#include <iostream>

// Declaring namespaces
using namespace std;

// Declaring functions
void functionTestIntel4002();

// MAIN
int main() {
    functionTestIntel4002();
    return 0;
}

// Functions
void functionTestIntel4002() {
    Intel4002 test;

    cout << test.isRAMAdrAccessable(BANK0, CHIP3, 65) << endl;
}