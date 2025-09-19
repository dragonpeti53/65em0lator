#include "memory.h"
#include <fstream>
#include <iostream>

std::streamsize fileSize(std::ifstream& file) {
    
    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    return size;
}

int initMemory(byte* memory, char* filename) {

    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        std::cout << "file couldnt be opened";
        return 1;
    }

    std::streamsize size = fileSize(file);
    if (size <= 0) {
        std::cout << "file cant be empty";
        return 1;
    }

    file.read(reinterpret_cast<char*>(memory), size);
    std::streamsize bytesRead = file.gcount();
    if (bytesRead < size) {
        std::cout << "not all bytes have been read";
        return 1;
    }

    return 0;
}
