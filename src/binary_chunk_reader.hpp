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
        uint64_t u = *_data;
        _data += 8;
        return u;
    }

    int64_t ReadLuaInteger() {
        int64_t i = *_data;
        _data += 8;
        return i;
    }

    double ReadLuaNumber() {
        double f = *_data;
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
        if(strcmp((char*)ReadBytes(4), LUA_SIGNATURE) != 0){
            throw "not a precompiled chunk!";
        }
        else if(ReadByte() != LUAC_VERSION){
            throw "version mismatch!";
        }
        else if(ReadByte() != LUAC_FORMAT){
            throw "format mismatch!";
        }
        else if((char*)ReadBytes(6) != LUAC_DATA){
            throw "corrupted!";
        }
        else if(ReadByte() != CINT_SIZE){
            throw "int size mismatch!";
        }
        else if(ReadByte() != CSIZET_SIZE){
            throw "size_t size mismatch!";
        }
        else if(ReadByte() != INSTRUCTION_SIZE){
            throw "instruction size mismatch!";
        }
        else if(ReadByte() != LUA_INTEGER_SIZE){
            throw "lua_Integer size mismatch!";
        }
        else if(ReadByte() != LUA_NUMBER_SIZE){
            throw "lua_Number size mismatch!";
        }
        else if(ReadLuaInteger() != LUAC_INT){
            throw "endianness mismatch!";
        }
        else if(ReadLuaNumber() != LUAC_NUM){
            throw "float format mismatch!";
        }

    }
};


#endif //LUA_DECOMPILER_BINARY_CHUNK_READER_HPP
