#include <iostream>

#include "src/binary_chunk_undumper.hpp"

int main() {


    FILE* file = fopen("../test_lua/hello_world.luac", "rb");

    if(!file) {
        assert(false && "failed to open file.");
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = new char[fileSize];

    fread(source, sizeof(byte), fileSize, file);
    fclose(file);

    Prototype p = *UnDump((byte*)source);
    

    return 0;
}
