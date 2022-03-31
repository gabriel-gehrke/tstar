#ifndef _LANGUAGE_H
#define _LANGUAGE_H

typedef unsigned int uint;
typedef unsigned short ushort;

typedef enum opcode
{
    OP_SKIP = 0,
    OP_CALC = 11,
    OP_CALC_O = 12,
    
    OP_JUMP = 31,
    OP_JUMP_V = 32,
    OP_CALL = 33,
    OP_RET = 34,

    OP_JUMP_C_N = 41,
    OP_JUMP_C = 42,

    OP_READCHAR = 56,
    OP_PRINTVAR = 57,
    OP_PRINTSTR = 58,

    OP_EXIT = 66,
} opcode_t;


typedef struct operation
{
    opcode_t opcode;
    ushort param;
} operation_t;


#endif // _LANGUAGE_H