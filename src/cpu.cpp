#include "cpu.h"

#include <cstdint>

#include "memory.h"

/*struct LookupTable {
    unsigned char cycles;
};*/

//void NOP_impl(CPU& cpu);



inline byte CPU::imm() {
    return fetch();
}

inline byte CPU::zpg() {
    return fetch();
}

inline byte CPU::zpx() {
    return (fetch() + X) & 0xFF;
}

inline byte CPU::zpy() {
    return (fetch() + Y) & 0xFF;
}

inline word CPU::abs() {
    byte lo = fetch();
    byte hi = fetch();

    return (hi << 8) | lo;
}

inline word CPU::abx() {
    return abs() + X;
}

inline word CPU::aby() {
    return abs() + Y;
}

inline word CPU::ind() {
    byte loptr = fetch();
    byte hiptr = fetch();
    word addr = (hiptr << 8) | loptr;

    byte lo = read(addr);
    byte hi;
    if ((addr & 0x00FF) == 0xFF) {
        hi = read(addr & 0xFF00);
    } else {
        hi = read(addr + 1);
    }

    return (hi << 8) | lo;
}

inline word CPU::inx() {
    byte ptr = (fetch() + X) & 0xFF;
    byte lo = read(ptr);
    byte hi = read((ptr + 1) & 0xFF);

    return (hi << 8) | lo;
}

inline word CPU::iny() {
    byte ptr = fetch();
    byte lo = read(ptr);
    byte hi = read((ptr + 1) & 0xFF);
    word addr = (hi << 8) | lo;
    return addr + Y;
}

inline word CPU::rel() {
    auto offset = static_cast<int8_t>(fetch());
    return PC + offset;
}


CPU::CPU() {
    setDispatchTable();
    setLookupTable();
}

bool CPU::getFlag(byte flag) const {
    return (SR & flag) != 0;
}

void CPU::setFlag(byte flag, bool value) {
    if (value)
        SR |= flag;
    else
        SR &= ~flag;
}

byte CPU::fetch() {
    return memory[PC++];
}

byte CPU::read(word addr) {
    return memory[addr];
}

void CPU::execute() {
    byte opcode = fetch();
    Func instruction = dispatchTable[opcode];
    cycles += lookupTable[opcode];

    (this->*instruction)();

    PC++;
}

void CPU::reset() {
    PC = memory[0xFFFC] | (memory[0xFFFD] << 8);
    SP = 0xFD;
    SR = 0x34;
    cycles = 7;
}

void CPU::setDispatchTable() {
    dispatchTable[0xA9] = &CPU::LDA_imm;
    dispatchTable[0xEA] = &CPU::NOP_impl;
    dispatchTable[0xA5] = &CPU::LDA_zpg;
    dispatchTable[0xB5] = &CPU::LDA_zpx;
    dispatchTable[0xAD] = &CPU::LDA_abs;
    dispatchTable[0xBD] = &CPU::LDA_abx;
}

void CPU::setLookupTable() {
    lookupTable[0xA9] = 2;
    lookupTable[0xEA] = 2;
    lookupTable[0xA5] = 3;
    lookupTable[0xB5] = 4;
    lookupTable[0xAD] = 4;
    lookupTable[0xBD] = 4;
}



void CPU::NOP_impl() {
    // nop
}

void CPU::LDA_imm() {
    A = imm();
    setFlag(CPU::Z, A == 0);
    setFlag(CPU::N, A & 0x80);
}

void CPU::LDA_zpg() {
    A = read(zpg());
    setFlag(CPU::Z, A == 0);
    setFlag(CPU::N, A & 0x80);
}

void CPU::LDA_zpx() {
    A = read(zpx());
    setFlag(CPU::Z, A == 0);
    setFlag(CPU::N, A & 0x80);
}

void CPU::LDA_abs() {
    A = read(abs());

    setFlag(CPU::Z, A == 0);
    setFlag(CPU::N, A & 0x80);
}

void CPU::LDA_abx() {
    A = read(abx());

    setFlag(CPU::Z, A == 0);
    setFlag(CPU::N, A & 0x80);
}

void CPU::LDA_aby() {
    A = read(aby());

    setFlag(CPU::Z, A == 0);
    setFlag(CPU::N, A & 0x80);
}
