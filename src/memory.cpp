#include "memory.h"

#include <cstdio>

int initMemory(byte *memory, char* filename) {
    FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		printf("Can't open file %s\n", filename);
		return -1;
	}

    //fseek(file, 0, SEEK_END);
    //fseek(file, 0, SEEK_SET);

    fread(memory, 65536, 1, file);

	return 0;
}
