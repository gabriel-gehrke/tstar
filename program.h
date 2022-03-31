#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "language.h"

typedef struct program
{
    operation_t* operations;
    uint length;
    uint capacity;
} program_t;

program_t* program_allocate(uint num_operations);
void program_free(program_t* p);
void program_ensure_capacity(program_t* p, uint num_operations);

#endif