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

void PrintCode(Prototype* p) {
    printf("functions\n");
    size_t codeCount = p->code.size();

    for (int i = 0; i < codeCount; ++i) {
        printf("\t%d\t[%d]\t0x%08x\n", i+1, p->lineInfos[i], p->code[i]);
    }
}

void PrintConstants(Prototype* p) {
    size_t constantCount = p->constants.size();
    printf("constants (%d):\n", (int)constantCount);

    for (int i = 0; i < constantCount; ++i) {
        printf("\t%d\t%s\n", i+1, p->constants[i].GetString());
    }
}

void PrintLocVars(Prototype* p) {
    size_t locVarCount = p->locVars.size();
    printf("locals (%d):\n", (int)locVarCount);

    for (int i = 0; i < locVarCount; ++i) {
        printf("\t%d\t%s\t%d\t%d\n",
               i, p->locVars[i].varName, p->locVars[i].startPc+1, p->locVars[i].endPc+1);
    }
}

void PrintUpValue(Prototype* p) {
    size_t upValuesCount = p->upValues.size();
    printf("upvalues (%d):\n", (int)upValuesCount);

    for (int i = 0; i < upValuesCount; ++i) {
        printf("\t%d\t%s\t%d\t%d\t%d\n",
               i, p->upValueNames[i], p->upValues[i].instack, p->upValues[i].idx, p->upValues[i].kind);
    }
}

void ListChunk(Prototype* prototype) {
    PrintHeader(prototype);
    PrintCode(prototype);
    PrintConstants(prototype);
    PrintLocVars(prototype);
    PrintUpValue(prototype);
}


#endif //LUA_DECOMPILER_BINARY_CHUNK_LOG_HPP
