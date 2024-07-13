/**
  ******************************************************************************
  * @file           : opcode_types.hpp
  * @author         : toastoffee
  * @brief          : None
  * @attention      : None
  * @date           : 2024/7/12
  ******************************************************************************
  */



#ifndef LUA_DECOMPILER_OPCODE_TYPES_HPP
#define LUA_DECOMPILER_OPCODE_TYPES_HPP

#include "binary_chunk_types.hpp"


const int IABC = 0,
          IABx = 1,
          IAsBx = 2,
          IAx = 3;

const int OP_MOVE = 0,        OP_LOADK = 1,       OP_LOADKX = 2,      OP_LOADBOOL = 3,
          OP_LOADNIL = 4,     OP_GETUPVAL = 5,    OP_GETTABUP = 6,    OP_GETTABLE = 7,
          OP_SETTABUP = 8,    OP_SETUPVAL = 9,    OP_SETTABLE = 10,   OP_NEWTABLE = 11,
          OP_SELF = 12,       OP_ADD = 13,        OP_SUB = 14,        OP_MUL = 15,
          OP_MOD = 16,        OP_POW = 17,        OP_DIV = 18,        OP_IDIV = 19,
          OP_BAND = 20,       OP_BOR = 21,        OP_BXOR = 22,       OP_SHL = 23,
          OP_SHR = 24,        OP_UNM = 25,        OP_BNOT = 26,       OP_NOT = 27,
          OP_LEN = 28,        OP_CONCAT = 29,     OP_JMP = 30,        OP_EQ = 31,
          OP_LT = 32,         OP_LE = 33,         OP_TEST = 34,       OP_TESTSET = 35,
          OP_CALL = 36,       OP_TAILCALL = 37,   OP_RETURN = 38,     OP_FORLOOP = 39,
          OP_FORPREP = 40,    OP_TFORCALL = 41,   OP_TFORLOOP = 42,   OP_SETLIST = 43,
          OP_CLOSURE = 44,    OP_VARARG = 45,     OP_EXTRAARG = 46;

const int OpArgN = 0, // argument is not used
          OpArgU = 1, // argument is used
          OpArgR = 2, // argument is a register or a jump offset
          OpArgK = 3; // argument is a constant or register/constant


struct Opcode {
    byte testFlag;      // operator is a test (next instruction must be a jump)
    byte setAFlag;      // instruction set register A
    byte argBMode;      // B arg mode
    byte argCMode;      // C arg mode
    byte opMode;
    const char* name;   // opcode name
};

const Opcode opcodes[] = {
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "MOVE    "},
        Opcode{0, 1, OpArgK, OpArgN, IABx,  "LOADK   "},
        Opcode{0, 1, OpArgN, OpArgN, IABx,  "LOADKX  "},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "LOADBOOL"},
        Opcode{0, 1, OpArgU, OpArgN, IABC,  "LOADNIL "},
        Opcode{0, 1, OpArgU, OpArgN, IABC,  "GETUPVAL"},
        Opcode{0, 1, OpArgU, OpArgK, IABC,  "GETTABUP"},
        Opcode{0, 1, OpArgR, OpArgK, IABC,  "GETTABLE"},
        Opcode{0, 0, OpArgK, OpArgK, IABC,  "SETTABUP"},
        Opcode{0, 0, OpArgU, OpArgN, IABC,  "SETUPVAL"},
        Opcode{0, 0, OpArgK, OpArgK, IABC,  "SETTABLE"},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "NEWTABLE"},
        Opcode{0, 1, OpArgR, OpArgK, IABC,  "SELF    "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "ADD     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "SUB     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "MUL     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "MOD     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "POW     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "DIV     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "IDIV    "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "BAND    "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "BOR     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "BXOR    "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "SHL     "},
        Opcode{0, 1, OpArgK, OpArgK, IABC,  "SHR     "},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "UNM     "},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "BNOT    "},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "NOT     "},
        Opcode{0, 1, OpArgR, OpArgN, IABC,  "LEN     "},
        Opcode{0, 1, OpArgR, OpArgR, IABC,  "CONCAT  "},
        Opcode{0, 0, OpArgR, OpArgN, IAsBx, "JMP     "},
        Opcode{1, 0, OpArgK, OpArgK, IABC,  "EQ      "},
        Opcode{1, 0, OpArgK, OpArgK, IABC,  "LT      "},
        Opcode{1, 0, OpArgK, OpArgK, IABC,  "LE      "},
        Opcode{1, 0, OpArgN, OpArgU, IABC,  "TEST    "},
        Opcode{1, 1, OpArgR, OpArgU, IABC,  "TESTSET "},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "CALL    "},
        Opcode{0, 1, OpArgU, OpArgU, IABC,  "TAILCALL"},
        Opcode{0, 0, OpArgU, OpArgN, IABC,  "RETURN  "},
        Opcode{0, 1, OpArgR, OpArgN, IAsBx, "FORLOOP "},
        Opcode{0, 1, OpArgR, OpArgN, IAsBx, "FORPREP "},
        Opcode{0, 0, OpArgN, OpArgU, IABC,  "TFORCALL"},
        Opcode{0, 1, OpArgR, OpArgN, IAsBx, "TFORLOOP"},
        Opcode{0, 0, OpArgU, OpArgU, IABC,  "SETLIST "},
        Opcode{0, 1, OpArgU, OpArgN, IABx,  "CLOSURE "},
        Opcode{0, 1, OpArgU, OpArgN, IABC,  "VARARG  "},
        Opcode{0, 0, OpArgU, OpArgU, IAx,   "EXTRAARG"},
};

#endif //LUA_DECOMPILER_OPCODE_TYPES_HPP
