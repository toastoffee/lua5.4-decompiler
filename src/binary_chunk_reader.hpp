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

private:
    byte ReadByte() {
        byte b = *_data;
        _data += 1;
        return b;
    }

    size_t ReadUnsigned() {
        size_t x = 0;
        uint8_t b;

        do {
            b = ReadByte();
            x = (x << 7) | (b & 0x7f);
        } while(((b & 0x80) == 0));

        return x;
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

    char* ReadString(){

        size_t size = ReadUnsigned() - 1; // the size should be (val - 1)
        char* str = (char*)ReadBytes(size);
        return str;
    }

    byte* ReadBytes(int n) {
        byte* bytes = new byte[n];
        strncpy((char*)bytes, (char*)_data, n);
        _data += n;
        return bytes;
    };

    Constant ReadConstant(){
        switch(ReadByte()){
            case TAG_NIL: {
                return {ConstantType::Nil, nullptr, 0};
            }
            case TAG_BOOLEAN:{
                bool b = ReadByte() != 0;
                return {ConstantType::Boolean, &b, sizeof(bool)};
            }
            case TAG_INTEGER:{
                int64_t i = ReadLuaInteger();
                return{ ConstantType::Integer, &i, sizeof(int64_t)};
            }
            case TAG_NUMBER:{
                double d = ReadLuaNumber();
                return{ConstantType::Number, &d, sizeof(double)};
            }
            case TAG_SHORT_STR:{
                char *s = ReadString();
                return{ConstantType::Str, s, (int)strlen(s)};
            }
            case TAG_LONG_STR:{
                char *s = ReadString();
                return{ConstantType::Str, s, (int)strlen(s)};
            }
            default:
                assert(false && "corrupted!");
        }
    }

    std::vector<uint32_t> ReadCode(){
        std::vector<uint32_t> codes;

        size_t size = ReadUnsigned();
        for (int i = 0; i < size; ++i) {
            codes.push_back(ReadUint32());
        }
        return codes;
    }

    std::vector<Constant> ReadConstants(){
        std::vector<Constant> constants;

        size_t size = ReadUnsigned();
        for(int i = 0; i < size; ++i){
            constants.push_back(ReadConstant());
        }

        return constants;
    }

    std::vector<UpValue> ReadUpValues(){
        std::vector<UpValue> upValues;

        uint32_t size = ReadUnsigned();

        for (int i = 0; i < size; ++i) {
            upValues.push_back({
                .instack = ReadByte(),
                .idx = ReadByte(),
                .kind = ReadByte()
            });
        }

        return upValues;
    }

    std::vector<Prototype*> ReadPrototypes(char *parentSource) {
        std::vector<Prototype*> protos;

        uint32_t size = ReadUnsigned();

        for (int i = 0; i < size; ++i) {
            protos.push_back(ReadPrototype(parentSource));
        }

        return protos;
    }

    std::vector<uint32_t> ReadLineInfo() {
        std::vector<uint32_t> lineInfos;

        uint32_t size = ReadUnsigned();

        for (int i = 0; i < size; ++i) {
            lineInfos.push_back(ReadByte());
        }

        return lineInfos;
    }

    std::vector<AbsLineInfo> ReadAbsLineInfos() {
        std::vector<AbsLineInfo> absLineInfos;

        uint32_t size = ReadUnsigned();

        for (int i = 0; i < size; ++i) {
            absLineInfos.push_back(AbsLineInfo{
                .pc = ReadUnsigned(),
                .line = ReadUnsigned()
            });
        }

        return absLineInfos;
    }

    std::vector<LocalVar> ReadLocVars() {
        std::vector<LocalVar> locVars;

        uint32_t size = ReadUnsigned();

        for (int i = 0; i < size; ++i) {
            locVars.push_back(LocalVar{
                .varName = ReadString(),
                .startPc = (uint32_t)ReadUnsigned(),
                .endPc = (uint32_t)ReadUnsigned()
            });
        }

        return locVars;
    }

    std::vector<char*> ReadUpValueNames() {
        std::vector<char*> upValueNames;

        uint32_t size = ReadUnsigned();

        for (int i = 0; i < size; ++i) {
            upValueNames.push_back(ReadString());
        }

        return upValueNames;
    }

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

    void SkipUpValueNum(){
        ReadByte();
    }

    Prototype* ReadPrototype(char *parentSource = "") {
        char *source = ReadString();

        if(strlen(source) == 0){
            source = parentSource;
        }

        Prototype* ret = new Prototype{
            .source = source,
            .lineDefined = (uint32_t)ReadUnsigned(),
            .lastLineDefined = (uint32_t)ReadUnsigned(),
            .numParams = ReadByte(),
            .isVararg = ReadByte(),
            .maxStackSize = ReadByte(),
            .code = ReadCode(),
            .constants = ReadConstants(),
            .upValues = ReadUpValues(),
            .prototypes = ReadPrototypes(source),
            .lineInfos = ReadLineInfo(),
            .absLineInfos = ReadAbsLineInfos(),
            .locVars = ReadLocVars(),
            .upValueNames = ReadUpValueNames()
        };

        return ret;
    }
};


#endif //LUA_DECOMPILER_BINARY_CHUNK_READER_HPP
