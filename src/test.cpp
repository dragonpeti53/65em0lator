#include "cpu.h"
#include "memory.h"
#include <cstdio>

int main(void) {
    CPU cpu;

    initMemory(memory, "test.bin");

    cpu.execute();

    printf("%x", cpu.A);

}