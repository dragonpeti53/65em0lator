#include "memory.h"

#include <cstdio>

void initMemory(byte *memory, char* filename) {
    FILE* file = fopen(filename, "rb");

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    fread(memory, 65536, 1, file);
}
