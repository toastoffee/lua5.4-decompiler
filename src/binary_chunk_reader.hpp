/**
  ******************************************************************************
  * @file           : binary_chunk_reader.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/9
  ******************************************************************************
  */



#ifndef LUA_DECOMPILER_BINARY_CHUNK_READER_HPP
#define LUA_DECOMPILER_BINARY_CHUNK_READER_HPP

#include "binary_chunk_types.hpp"

class BinaryChunkReader {
private:
    byte* _data;

public:
    byte ReadByte() {
        byte b = *_data;
        _data  += 1;
        return b;
    }

    uint32_t ReadUint32() {
        uint32_t u = *_data;
        _data += 4;
        return u;
    }

    uint64_t ReadUint64() {
        uint64_t u;
        memcpy(&u, _data, sizeof(uint64_t));
        _data += 8;
        return u;
    }

    int64_t ReadLuaInteger() {
        int64_t i;
        memcpy(&i, _data, sizeof(int64_t));
        _data += 8;
        return i;
    }

    double ReadLuaNumber() {
        double f;
        memcpy(&f, _data, sizeof(double));
        _data += 8;
        return f;
    }

    const char* ReadString(){
        uint8_t size = ReadByte();
        if(size == 0){
            return "";
        }else if(size == 0xFF){
            size = uint8_t(ReadUint64());
        }

        char* str = (char*)ReadBytes(size);
        return str;
    }

    byte* ReadBytes(int n) {
        byte* bytes = new byte[n];
        strncpy((char*)bytes, (char*)_data, n);
        _data += n;
        return bytes;
    };

public:

    explicit BinaryChunkReader(byte* data) : _data(data) { }

    void CheckHeader() {

        assert(strcmp((char*)ReadBytes(4), LUA_SIGNATURE) == 0 && "not a precompiled chunk!");

        assert(ReadByte() == LUAC_VERSION && "version mismatch!");

        assert(ReadByte() == LUAC_FORMAT && "format mismatch!");

        assert(strcmp((char*)ReadBytes(6), LUAC_DATA) == 0 && "corrupted!");

        assert(ReadByte() == INSTRUCTION_SIZE && "instruction size mismatch!");

        assert(ReadByte() == LUA_INTEGER_SIZE && "lua_Integer size mismatch!");

        assert(ReadByte() == LUA_NUMBER_SIZE && "lua_Number size mismatch!");

        assert(ReadLuaInteger() == LUAC_INT && "endianness mismatch");

        assert(ReadLuaNumber() == LUAC_NUM && "float format mismatch!");

    }
};


#endif //LUA_DECOMPILER_BINARY_CHUNK_READER_HPP
