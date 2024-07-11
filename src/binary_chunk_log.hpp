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

    const char* varargFlag = "";
    if(prototype->isVararg > 0) { varargFlag = "+"; }

    printf("\n%s <%s:%d,%d> (%d instructions)\n",
           funcType, prototype->source, prototype->lineDefined, (int)prototype->code.size());

    printf("%d%s params, %d slots, %d upValues, ",
           prototype->numParams, varargFlag, prototype->maxStackSize, (int)prototype->upValues.size());

    printf("%d locals, %d constants, %d functions\n",
           (int)prototype->locVars.size(), (int)prototype->constants.size(), (int)prototype->prototypes.size());
}


void ListChunk(Prototype* prototype) {
    PrintHeader(prototype);
}


#endif //LUA_DECOMPILER_BINARY_CHUNK_LOG_HPP
