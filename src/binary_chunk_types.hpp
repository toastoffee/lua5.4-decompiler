/**
  ******************************************************************************
  * @file           : binary_chunk_types.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/9
  ******************************************************************************
  */



#ifndef LUA_DECOMPILER_BINARY_CHUNK_TYPES_HPP
#define LUA_DECOMPILER_BINARY_CHUNK_TYPES_HPP

#include <stdint.h>

typedef uint8_t byte;

const char*  LUA_SIGNATURE    = "\x1bLua";
const int    LUAC_VERSION     = 0x54;
const int    LUAC_FORMAT      = 0;
const char*  LUAC_DATA        = "\x19\x93\r\n\x1a\n";
const int    CINT_SIZE        = 4;
const int    CSIZET_SIZE      = 4;
const int    INSTRUCTION_SIZE = 4;
const int    LUA_INTEGER_SIZE = 8;
const int    LUA_NUMBER_SIZE  = 8;
const int    LUAC_INT         = 0x5678;
const double LUAC_NUM         = 370.5;

struct Header {
    byte    signature[4];    // signature, magic number:0x1B4C7561
    byte    version;         // version, major_ver * 16 + minor_ver
    byte    format;          // format, 0 is official
    byte    luacData[6];     // LUAC_DATA, former 2 bytes are 0x1993(lua release year), then 0x0D, 0x0A, 0x1A, 0x0A
    byte    cintSize;        // cint size, usually 4 bytes
    byte    sizetSize;       // size_t size, usually 8 bytes
    byte    instructionSize; // lua instruction size, usually 4 bytes
    byte    luaIntegerSize;  // lua integer size, usually 8 bytes
    byte    luaNumberSize;   // lua double number size, usually 8 bytes
    int64_t luacInt;         // LUAC_INT, 0x5678(size depends on lua Integer size) to set big-end or small-end
    double  luacNum;         // LUAC_NUM, 370.5(size depends on lua double size) to check float format, usually IEEE 754
};

struct binaryChunk {
    Header      header;
    byte        upValues_size;
    Prototype*  mainFunc;
};

#endif //LUA_DECOMPILER_BINARY_CHUNK_TYPES_HPP
