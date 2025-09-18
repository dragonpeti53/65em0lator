#include "cpu.h"
#include "memory.h"
#include <cstdio>

int main(int argc, char **argv) {
    CPU cpu;

    char* filename = argv[1];

    if( (initMemory(memory, filename)) == (-1)) return -1;

    cpu.execute();

    //printf("%x", cpu.A);

    if (cpu.A == 255) {
        puts("success");
    }
}