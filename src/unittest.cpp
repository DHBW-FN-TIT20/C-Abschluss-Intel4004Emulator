// Replace Intel4004 with your Intel4004 class name
#define INTEL_MCS4_CLASS Intel4004

#define _UNITTEST_
#ifdef _UNITTEST_
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_MAIN
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include "..\inc\catch.hpp"
    #include "..\4004\4004.h"
#elif __unix__
	#include "../inc/catch.hpp"
    #include "../4004/4004.h"
#endif

#include <cstdint>

typedef enum : uint8_t {
    NOP,
    JCN_0 = 0x10,
    JCN_1,
    JNT = 0x11,
    JCN_2,
    JC = 0x12,
    JCN_3,
    JCN_4,
    JZ = 0x14,
    JCN_5,
    JCN_6,
    JCN_7,
    JCN_8,
    JCN_9,
    JT = 0x19,
    JCN_10,
    JNC = 0x1A,
    JCN_11,
    JCN_12,
    JNZ = 0x1C,
    JCN_13,
    JCN_14,
    JCN_15,
    FIM_0,
    SRC_0,
    FIM_2,
    SRC_2,
    FIM_4,
    SRC_4,
    FIM_6,
    SRC_6,
    FIM_8,
    SRC_8,
    FIM_10,
    SRC_10,
    FIM_12,
    SRC_12,
    FIM_14,
    SRC_14,
    FIN_0,
    JIN_0,
    FIN_2,
    JIN_2,
    FIN_4,
    JIN_4,
    FIN_6,
    JIN_6,
    FIN_8,
    JIN_8,
    FIN_10,
    JIN_10,
    FIN_12,
    JIN_12,
    FIN_14,
    JIN_14,
    JUN_0,
    JUN_1,
    JUN_2,
    JUN_3,
    JUN_4,
    JUN_5,
    JUN_6,
    JUN_7,
    JUN_8,
    JUN_9,
    JUN_10,
    JUN_11,
    JUN_12,
    JUN_13,
    JUN_14,
    JUN_15,
    JMS_0,
    JMS_1,
    JMS_2,
    JMS_3,
    JMS_4,
    JMS_5,
    JMS_6,
    JMS_7,
    JMS_8,
    JMS_9,
    JMS_10,
    JMS_11,
    JMS_12,
    JMS_13,
    JMS_14,
    JMS_15,
    INC_0,
    INC_1,
    INC_2,
    INC_3,
    INC_4,
    INC_5,
    INC_6,
    INC_7,
    INC_8,
    INC_9,
    INC_10,
    INC_11,
    INC_12,
    INC_13,
    INC_14,
    INC_15,
    ISZ_0,
    ISZ_1,
    ISZ_2,
    ISZ_3,
    ISZ_4,
    ISZ_5,
    ISZ_6,
    ISZ_7,
    ISZ_8,
    ISZ_9,
    ISZ_10,
    ISZ_11,
    ISZ_12,
    ISZ_13,
    ISZ_14,
    ISZ_15,
    ADD_0,
    ADD_1,
    ADD_2,
    ADD_3,
    ADD_4,
    ADD_5,
    ADD_6,
    ADD_7,
    ADD_8,
    ADD_9,
    ADD_10,
    ADD_11,
    ADD_12,
    ADD_13,
    ADD_14,
    ADD_15,
    SUB_0,
    SUB_1,
    SUB_2,
    SUB_3,
    SUB_4,
    SUB_5,
    SUB_6,
    SUB_7,
    SUB_8,
    SUB_9,
    SUB_10,
    SUB_11,
    SUB_12,
    SUB_13,
    SUB_14,
    SUB_15,
    LD_0,
    LD_1,
    LD_2,
    LD_3,
    LD_4,
    LD_5,
    LD_6,
    LD_7,
    LD_8,
    LD_9,
    LD_10,
    LD_11,
    LD_12,
    LD_13,
    LD_14,
    LD_15,
    XCH_0,
    XCH_1,
    XCH_2,
    XCH_3,
    XCH_4,
    XCH_5,
    XCH_6,
    XCH_7,
    XCH_8,
    XCH_9,
    XCH_10,
    XCH_11,
    XCH_12,
    XCH_13,
    XCH_14,
    XCH_15,
    BBL_0,
    BBL_1,
    BBL_2,
    BBL_3,
    BBL_4,
    BBL_5,
    BBL_6,
    BBL_7,
    BBL_8,
    BBL_9,
    BBL_10,
    BBL_11,
    BBL_12,
    BBL_13,
    BBL_14,
    BBL_15,
    LDM_0,
    LDM_1,
    LDM_2,
    LDM_3,
    LDM_4,
    LDM_5,
    LDM_6,
    LDM_7,
    LDM_8,
    LDM_9,
    LDM_10,
    LDM_11,
    LDM_12,
    LDM_13,
    LDM_14,
    LDM_15,
    WRM,
    WMP,
    WRR,
    WPM,
    WR0,
    WR1,
    WR2,
    WR3,
    SBM,
    RDM,
    RDR,
    ADM,
    RD0,
    RD1,
    RD2,
    RD3,
    CLB,
    CLC,
    IAC,
    CMC,
    CMA,
    RAL,
    RAR,
    TCC,
    DAC,
    TCS,
    STC,
    DAA,
    KBP,
    DCL
} COMMAND;

TEST_CASE("UnitTest_Intel4004") {
    SECTION("NOP") {
        /**
         * NOP          1
         * NOP          1
         */

        uint8_t source[] = { NOP, NOP };

        INTEL_MCS4_CLASS instance;
        Intel4004Base *processor = { &instance };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 2);

        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK(processor->getTicks() == 0);
        // NOP
        processor->nextCommand();
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());

        CHECK(processor->getTicks() == 1);
    }
    SECTION("JCN") {
        /**
         * JCN_0 0x03   1   JUMP to 0x03 because carry=0
         * NOP          0
         * CMC          1   set carry=1
         * JCN_0 0x07   1   no JUMP because no condition is true
         * NOP          1
         * JCN_1 0x0A   1   JUMP to 0x0A because testPin=0
         * NOP          0
         * JCN_2 0x0D   1   JUMP to 0x0D because carry=1
         * NOP          0
         * JCN_4 0x10   1   JUMP to 0x10 because accumulator=0
         * NOP          0
         * JCN_9 0x13   1   no JUMP because testPin!=1
         * NOP          1
         * JCN_10 0x16  1   no JUMP becuase carry!=0
         * NOP          1   
         * JCN_12 0x19  1   no JUMP because accumulator=0
         * NOP          1
         * JCN_15 0x1C  1   JUMP to 0x1C because every condition is true
         * NOP          0
         * NOP          1
         */

        uint8_t source[] = { JCN_0, 0x03, NOP, CMC, JCN_0, 0x07, NOP, JCN_1, 0x0A, NOP, JCN_2, 0x0D, NOP, JCN_4, 0x10, NOP, JCN_9, 0x13, NOP, JCN_10, 0x16, NOP, JCN_12, 0x19, NOP, JCN_15, 0x1C, NOP, NOP };

        INTEL_MCS4_CLASS instance;
        Intel4004Base *processor = { &instance };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 29);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        // JCN_0 0x03
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x03);
        // CMC
        processor->nextCommand();
        CHECK(processor->getCarry());
        CHECK(processor->getPC().banked.address == 0x04);
        // JCN_0 0c07
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x06);
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x07);
        // JCN_1 0x0A
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x0A);
        // JCN_2 0x0D
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x0D);
        // JCN_4 0x10
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x10);
        // JCN_9 0x13
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x12);
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x13);
        // JCN_10 0x16
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x15);
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x16);
        // JCN_12 0x19
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x18);
        // NOP
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x19);
        // JCN_15 0x1C
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1C);

        CHECK(processor->getTicks() == 23);

        // RESET Processor to test jump at ROM-END
        processor->reset();

        /**
         * JCN_4 0xFE   1   JUMP to 0xFE because accumulator=0
         * JCN_4 0x02   1   JUMP to 0x02 of next ROM-Cell because accumulator=0 and JCN in last two positions of ROM
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * NOP          1
         */

        uint8_t sourceTwo[261];

        for (int i = 0; i < 261; i++) {
            sourceTwo[i] = 0x00;
        }

        sourceTwo[0] = JCN_4;
        sourceTwo[1] = 0xFE;
        sourceTwo[0xFE] = JCN_4;
        sourceTwo[0xFF] = 0x02;
        sourceTwo[0x102] = FIM_0;
        sourceTwo[0x103] = 0x02;
        sourceTwo[0x104] = NOP;

        CHECK(processor->getPtrToROM()->writeFrom(sourceTwo, sizeof(sourceTwo)) == 261);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        // JCN_4 0xFE
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0xFE);
        // JCN_4 0x02
        processor->nextCommand();
        CHECK(processor->getPC().banked.bank == 0x1);
        CHECK(processor->getPC().banked.address == 0x02);
        // FIM_0 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x02);

        CHECK(processor->getTicks() == 6);
    }
    SECTION("FIM") {
        /**
         * FIM_0 0x11   1   fetch 0x11 to register pair 0
         * FIM_2 0x02   1   fetch 0x02 to register pair 2
         * FIM_4 0x04   1   fetch 0x04 to register pair 4
         * FIM_6 0x06   1   fetch 0x06 to register pair 6
         * FIM_8 0x08   1   fetch 0x08 to register pair 8
         * FIM_10 0x0A  1   fetch 0x0A to register pair 10
         * FIM_12 0xOC  1   fetch 0x0C to register pair 12
         * FIM_14 0x0E  1   fetch 0x0E to register pair 14
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x11, FIM_2, 0x02, FIM_4, 0x04, FIM_6, 0x06, FIM_8, 0x08, FIM_10, 0x0A, FIM_12, 0x0C, FIM_14, 0x0E, NOP };

        INTEL_MCS4_CLASS instance;
        Intel4004Base *processor = { &instance };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 17);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        CHECK_FALSE(processor->getRegisterPair(Pair_R5_R4));
        CHECK_FALSE(processor->getRegisterPair(Pair_R7_R6));
        CHECK_FALSE(processor->getRegisterPair(Pair_R9_R8));
        CHECK_FALSE(processor->getRegisterPair(Pair_R11_R10));
        CHECK_FALSE(processor->getRegisterPair(Pair_R13_R12));
        CHECK_FALSE(processor->getRegisterPair(Pair_R15_R14));
        // FIM_0 0x11
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x11);
        CHECK(processor->getPC().banked.address == 0x02);
        // FIM_2 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x02);
        // FIM_4 0x04
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R5_R4) == 0x04);
        // FIM_6 0x06
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R7_R6) == 0x06);
        // FIM_8 0x08
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R9_R8) == 0x08);
        // FIM_10 0x0A
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R11_R10) == 0x0A);
        // FIM_12 0x0C
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R13_R12) == 0x0C);
        // FIM_14 0x0E
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R15_R14) == 0x0E);

        CHECK(processor->getTicks() == 16);
    }
    SECTION("FIN") {
        /**
         * FIN_0        1   fetch FIN_0 at 0x00 to register pair 0
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * FIN_2        1   fetch 0x02 at 0x02 to register pair 2
         * FIN_4        1   fetch 0x02 at 0x02 to register pair 4
         * FIN_6        1   fetch 0x02 at 0x02 to register pair 6
         * FIN_8        1   fetch 0x02 at 0x02 to register pair 8
         * FIN_10       1   fetch 0x02 at 0x02 to register pair 10
         * FIN_12       1   fetch 0x02 at 0x02 to register pair 12
         * FIN_14       1   fetch 0x02 at 0x02 to register pair 14
         * NOP          1
         */

        uint8_t source[] = { FIN_0, FIM_0, 0x02, FIN_2, FIN_4, FIN_6, FIN_8, FIN_10, FIN_12, FIN_14, NOP };

        INTEL_MCS4_CLASS instance;
        Intel4004Base *processor = { &instance };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 11);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        CHECK_FALSE(processor->getRegisterPair(Pair_R5_R4));
        CHECK_FALSE(processor->getRegisterPair(Pair_R7_R6));
        CHECK_FALSE(processor->getRegisterPair(Pair_R9_R8));
        CHECK_FALSE(processor->getRegisterPair(Pair_R11_R10));
        CHECK_FALSE(processor->getRegisterPair(Pair_R13_R12));
        CHECK_FALSE(processor->getRegisterPair(Pair_R15_R14));
        // FIN_0
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == FIN_0);
        // FIM_0 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x02);
        // FIN_2
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x02);
        // FIN_4
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R5_R4) == 0x02);
        // FIN_6
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R7_R6) == 0x02);
        // FIN_8
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R9_R8) == 0x02);
        // FIN_10
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R11_R10) == 0x02);
        // FIN_12
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R13_R12) == 0x02);
        // FIN_14
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R15_R14) == 0x02);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());

        CHECK(processor->getTicks() == 10);

        // RESET Processor to test jump at ROM-END
        processor->reset();

        /**
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * JCN_4 0xFF   1   JUMP to 0xFF because accumulator=0
         * FIN_2        1   fetch 0x3A at 0x102 to register pair 2
         * NOP          1
         * NOP          1
         */

        uint8_t sourceTwo[261];

        for (int i = 0; i < 261; i++) {
            sourceTwo[i] = 0x00;
        }

        sourceTwo[0] = FIM_0;
        sourceTwo[1] = 0x03;
        sourceTwo[2] = JCN_4;
        sourceTwo[3] = 0xFF;
        sourceTwo[0xFF] = FIN_2;
        sourceTwo[0x100] = NOP;
        sourceTwo[0x101] = NOP;
        sourceTwo[0x102] = 0x3A;

        CHECK(processor->getPtrToROM()->writeFrom(sourceTwo, sizeof(sourceTwo)) == 261);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        // FIM_0 0x02
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x02);
        // JCN_4 0xFF
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0xFF);
        // FIN_2
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x3A);

        CHECK(processor->getTicks() == 5);
    }
    SECTION("JIN") {
        /**
         * FIM_0 0x12
         * FIM_2 0x14
         * FIM_4 0x16
         * FIM_6 0x18
         * FIM_8 0x1A
         * FIM_10 0x1C
         * FIM_12 0x1E
         * FIM_14 0x20
         * JIN_0        1
         * NOP          0
         * JIN_2        1
         * NOP          0
         * JIN_4        1
         * NOP          0
         * JIN_6        1
         * NOP          0
         * JIN_8        1
         * NOP          0
         * JIN_10       1
         * NOP          0
         * JIN_12       1
         * NOP          0
         * JIN_14       1
         * NOP          0
         * NOP          1
         */

        uint8_t source[] = { FIM_0, 0x12, FIM_2, 0x14, FIM_4, 0x16, FIM_6, 0x18, FIM_8, 0x1A, FIM_10, 0x1C, FIM_12, 0x1E, FIM_14, 0x20, JIN_0, NOP, JIN_2, NOP, JIN_4, NOP, JIN_6, NOP, JIN_8, NOP, JIN_10, NOP, JIN_12, NOP, JIN_14, NOP, NOP };

        INTEL_MCS4_CLASS instance;
        Intel4004Base *processor = { &instance };

        CHECK(processor->getPtrToROM()->writeFrom(source, sizeof(source)) == 33);

        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        CHECK_FALSE(processor->getRegisterPair(Pair_R3_R2));
        CHECK_FALSE(processor->getRegisterPair(Pair_R5_R4));
        CHECK_FALSE(processor->getRegisterPair(Pair_R7_R6));
        CHECK_FALSE(processor->getRegisterPair(Pair_R9_R8));
        CHECK_FALSE(processor->getRegisterPair(Pair_R11_R10));
        CHECK_FALSE(processor->getRegisterPair(Pair_R13_R12));
        CHECK_FALSE(processor->getRegisterPair(Pair_R15_R14));
        // FIM_0 0x12
        processor->nextCommand();
        // FIM_2 0x14
        processor->nextCommand();
        // FIM_4 0x16
        processor->nextCommand();
        // FIM_6 0x18
        processor->nextCommand();
        // FIM_8 0x1A
        processor->nextCommand();
        // FIM_10 0x1C
        processor->nextCommand();
        // FIM_12 0x1E
        processor->nextCommand();
        // FIM_14 0x20
        processor->nextCommand();
        CHECK(processor->getRegisterPair(Pair_R1_R0) == 0x12);
        CHECK(processor->getRegisterPair(Pair_R3_R2) == 0x14);
        CHECK(processor->getRegisterPair(Pair_R5_R4) == 0x16);
        CHECK(processor->getRegisterPair(Pair_R7_R6) == 0x18);
        CHECK(processor->getRegisterPair(Pair_R9_R8) == 0x1A);
        CHECK(processor->getRegisterPair(Pair_R11_R10) == 0x1C);
        CHECK(processor->getRegisterPair(Pair_R13_R12) == 0x1E);
        CHECK(processor->getRegisterPair(Pair_R15_R14) == 0x20);
        CHECK(processor->getPC().banked.address == 0x10);
        // JIN_0
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x12);
        // JIN_2
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x14);
        // JIN_4
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x16);
        // JIN_6
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x18);
        // JIN_8
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1A);
        // JIN_10
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1C);
        // JIN_12
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x1E);
        // JIN_14
        processor->nextCommand();
        CHECK(processor->getPC().banked.address == 0x20);

        CHECK(processor->getTicks() == 24);

        // RESET Processor to test jump at ROM-END
        processor->reset();

        /**
         * FIM_0 0x02   1   fetch 0x02 to register pair 0
         * JCN_4 0xFF   1   JUMP to 0xFF because accumulator=0
         * JIN_0        1   JUMP to 0x102
         * NOP          1
         * NOP          1
         */

        uint8_t sourceTwo[261];

        for (int i = 0; i < 261; i++) {
            sourceTwo[i] = 0x00;
        }

        sourceTwo[0] = FIM_0;
        sourceTwo[1] = 0x03;
        sourceTwo[2] = JCN_4;
        sourceTwo[3] = 0xFF;
        sourceTwo[0xFF] = JIN_0;
        sourceTwo[0x100] = NOP;
        sourceTwo[0x101] = NOP;
        sourceTwo[0x102] = NOP;

        CHECK(processor->getPtrToROM()->writeFrom(sourceTwo, sizeof(sourceTwo)) == 261);

        REQUIRE(processor->getPC().banked.bank == 0x0);
        REQUIRE(processor->getPC().banked.address == 0x00);
        CHECK_FALSE(processor->getCarry());
        CHECK_FALSE(processor->getAccumulator());
        CHECK_FALSE(processor->getTestPin());
        CHECK_FALSE(processor->getRegisterPair(Pair_R1_R0));
        // FIM_0 0x02
        processor->nextCommand();
        
    }
    SECTION("JUM") {
    }
    SECTION("JMS") {
    }
    SECTION("INC") {
    }
    SECTION("ISZ") {
    }
    SECTION("ADD") {
    }
    SECTION("SUB") {
    }
    SECTION("LD") {
    }
    SECTION("XCH") {
    }
    SECTION("BBL") {
    }
    SECTION("LDM") {
    }
    SECTION("CLB") {
    }
    SECTION("CLC") {
    }
    SECTION("IAC") {
    }
    SECTION("CMC") {
    }
    SECTION("RAL") {
    }
    SECTION("RAR") {
    }
    SECTION("TCC") {
    }
    SECTION("DAC") {
    }
    SECTION("TCS") {
    }
    SECTION("STC") {
    }
    SECTION("DAA") {
    }
    SECTION("KBP") {
    }
    SECTION("DCL") {
    }
    SECTION("SRC") {
    }
    SECTION("WRM") {
    }
    SECTION("WMP") {
    }
    SECTION("WRR") {
    }
    SECTION("WPM") {
    }
    SECTION("WR0") {
    }
    SECTION("WR1") {
    }
    SECTION("WR2") {
    }
    SECTION("WR3") {
    }
    SECTION("SBM") {
    }
    SECTION("RDM") {
    }
    SECTION("RDR") {
    }
    SECTION("ADM") {
    }
    SECTION("RD0") {
    }
    SECTION("RD1") {
    }
    SECTION("RD2") {
    }
    SECTION("RD3") {
    }
}
#endif