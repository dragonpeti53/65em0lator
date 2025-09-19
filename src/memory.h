#include <fstream>
#ifndef MEMORY_H
#define MEMORY_H

using byte = unsigned char;

inline byte memory[65536];

int initMemory(byte *mem, char* filename);

std::streamsize fileSize(std::ifstream& file);

#endif //MOS6502_MEMORY_H