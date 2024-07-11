/**
  ******************************************************************************
  * @file           : binary_chunk_dumper.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/9
  ******************************************************************************
  */



#ifndef LUA_DECOMPILER_BINARY_CHUNK_DUMPER_HPP
#define LUA_DECOMPILER_BINARY_CHUNK_DUMPER_HPP


#include "binary_chunk_types.hpp"
#include "binary_chunk_reader.hpp"

Prototype* UnDump(byte data[]){
    BinaryChunkReader reader(data);
    reader.CheckHeader();
    reader.SkipUpValueNum();
    Prototype* proto = reader.ReadPrototype();
    return proto;
}


#endif //LUA_DECOMPILER_BINARY_CHUNK_DUMPER_HPP
