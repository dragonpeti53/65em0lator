#include "types.h"

#ifndef CPU_H
#define CPU_H



struct CPU;

using DispatchTable = void (CPU::*)(); //opcode to function matching
using Func = void (CPU::*)();
using LookupTable = unsigned char; //cycles

struct CPU {

    int cycles = 0;

    //byte memory = memory;

    word PC = 0;
    byte SP = 0;

    byte A = 0;
    byte X = 0;
    byte Y = 0;

    byte SR = 0x24;

    enum FLAGS {
        C = 1 << 0,  // Carry
        Z = 1 << 1,  // Zero
        I = 1 << 2,  // Interrupt Disable
        D = 1 << 3,  // Decimal Mode
        B = 1 << 4,  // Break
        U = 1 << 5,  // Unused (always 1)
        V = 1 << 6,  // Overflow
        N = 1 << 7   // Negative
    };

    CPU();

    [[nodiscard]] bool getFlag(byte flag) const;

    void setFlag(byte flag, bool value);

    byte fetch();

    byte read(word addr);

    DispatchTable dispatchTable[256]{};

    LookupTable lookupTable[256]{};

    void setDispatchTable();
    void setLookupTable();

    void execute();

    void reset();

    //addressing

    inline byte imm();
    inline byte zpg();
    inline byte zpx();
    inline byte zpy();
    inline word abs();
    inline word abx();
    inline word aby();
    inline word ind();
    inline word inx();
    inline word iny();
    inline word rel();

    //instructions

    void NOP_impl();
    void LDA_imm();
    void LDA_zpg();
    void LDA_zpx();
    void LDA_abs();
    void LDA_abx();
    void LDA_aby();
};



#endif //MOS6502_CPU_H