#include <stdlib.h>
#include <stdio.h>
#include "program.h"

program_t* program_allocate(uint num_operations)
{
    program_t* p = (program_t*) malloc(sizeof(program_t));
    if (!p)
    {
        perror("Program allocation failed");
        exit(1);
    }
    p->operations = malloc(num_operations * sizeof(operation_t));
    if (!p->operations)
    {
        perror("Operation array allocation failed");
        exit(1);
    }
    p->length = 0;
    p->capacity = num_operations;
    return p;
}

static inline uint max(uint a, uint b)
{
    return a > b ? a : b;
}

void program_ensure_capacity(program_t* p, uint num_operations)
{
    if (p->capacity < num_operations)
    {
        p->capacity = max(num_operations, p->capacity * 2);
        p->operations = realloc(p->operations, sizeof(operation_t) * p->capacity);
        if (!p->operations)
        {
            perror("Resizing the operations array failed");
            exit(1);
        }
    }
}

void program_free(program_t* p)
{
    free(p->operations);
    free(p);
}