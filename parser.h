#ifndef _PARSER_H
#define _PARSER_H

#include "language.h"
#include "program.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool parse_line(const char* s, operation_t* out);
program_t* parse_program(FILE* stream);


#endif // _PARSER_H