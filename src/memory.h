#ifndef MOS6502_MEMORY_H
#define MOS6502_MEMORY_H

using byte = unsigned char;

inline byte memory[65536];

int initMemory(byte *mem, char* filename);

#endif //MOS6502_MEMORY_H