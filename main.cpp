#include <iostream>

#include "src/binary_chunk_reader.hpp"

int main() {

    char *source = "\u001BLuaT\u0000\u0019�\n\"\"\u001A\n\"\"\u0004\b\bxV\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000\u0000(w@\u0001�@hello_world.lua��\u0000\u0001\u0002�Q\u0000\u0000\u0000\u000B\u0000\u0000\u0000��\u0000\u0000D\u0000\u0002\u0001F\u0000\u0001\u0001�\u0004�print\u0004�hello,world!�\u0001\u0000\u0000��\u0001\u0000\u0000\u0000\u0000����_ENV";

    BinaryChunkReader reader((byte*) source);

    reader.CheckHeader();

    return 0;
}
