/**
  ******************************************************************************
  * @file           : binary_chunk_log.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/11
  ******************************************************************************
  */



#ifndef LUA_DECOMPILER_BINARY_CHUNK_LOG_HPP
#define LUA_DECOMPILER_BINARY_CHUNK_LOG_HPP

#include "binary_chunk_types.hpp"

void PrintHeader(Prototype* prototype) {
    const char* funcType = "main";
    if(prototype->lineDefined > 0) { funcType = "function"; }
    
}


#endif //LUA_DECOMPILER_BINARY_CHUNK_LOG_HPP
