/*
 * main.cpp
 *
 *  Created on: 31.01.2021
 *      Author: Thomas Staudacher
 */

#include <MCS4BaseClasses.h>
#include <400x_GlobalDefines.h>
#include <easylogging++.h>
INITIALIZE_EASYLOGGINGPP

#ifdef _UNITTEST_
#define CATCH_CONFIG_FAST_COMPILE	//Beschleunigte Compilierung
#define CATCH_CONFIG_MAIN			//Main Routine mit Menuefuehrung
#include <catch.hpp>				//Sourcen von Catch2

void setUp() {
	//Logging einschalten
	el::Configurations conf("logging.ini");
	el::Loggers::reconfigureAllLoggers(conf);

	LOG(INFO) << "Unittest MCS4 System gestartet";
}

void tearDown() {
	LOG(INFO) << "Unittest MCS4 System beendet";
}
#else
int main() {
	//Logging einschalten
	el::Configurations conf("logging.ini");
	el::Loggers::reconfigureAllLoggers(conf);

	LOG(INFO) << "Simulation MCS4 System gestartet";
	Intel4004 mcs4;

	mcs4.reset();
	LOG(INFO) << "Simulation MCS4 System beendet";
	return 0;
}
#endif

//Dieser Define wird später beim compilieren mit -DIntel4004 übergeben (wenn die Hauptklasse so heisst)
//Ein ähnliche Konstrukt wird auch für den Include des Headers implementiert
#define INTEL_MCS4_CLASS Intel4004

#define _SIMPLE_TESTS_
#ifdef _SIMPLE_TESTS_
TEST_CASE("SimpleTest") {
	SECTION("Command_CLB") {

		/* Source
		 * ldm 0
		 * dac
		 * clb
		 * nop
		 */

		uint8_t source[] = { 0xD0, 0xF8, 0xF0, 0x00 };

		INTEL_MCS4_CLASS instance;
		Intel4004Base *processor = { &instance };

		CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 4);

		CHECK_FALSE(processor->getCarry());
		CHECK_FALSE(processor->getAccumulator());
		processor->nextCommand();
		CHECK_FALSE(processor->getCarry());
		CHECK_FALSE(processor->getAccumulator());
		processor->nextCommand();
		CHECK(processor->getCarry());
		CHECK(processor->getAccumulator() == 15);
		processor->nextCommand();
		CHECK_FALSE(processor->getCarry());
		CHECK_FALSE(processor->getAccumulator());
		CHECK((Intel4004::CYCLES_PER_INSTRUCTION * 3) == processor->getTicks());
	}

	SECTION("CMC") {

		/* Source
		 * clc
		 * cmc
		 * nop
		 */

		uint8_t source[] = { 0xF1, 0xF3, 0x00 };

		INTEL_MCS4_CLASS instance;
		Intel4004Base *processor = { &instance };

		CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 3);

		CHECK_FALSE(processor->getCarry());
		processor->nextCommand();
		CHECK_FALSE(processor->getCarry());
		processor->nextCommand();
		CHECK(processor->getCarry());
		CHECK((Intel4004::CYCLES_PER_INSTRUCTION * 2) == processor->getTicks());
	}
}
#endif

