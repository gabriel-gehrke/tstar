#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int main(int argc, const char** args)
{
    if (argc != 2)
    {
        fputs("Invalid number of arguments", stderr);
        return 1;
    }

    const char* fn = args[1];
    FILE* file = fopen(fn, "r");
    if (file == NULL)
    {
        perror("An error occured during opening the file");
        exit(1);
    }

    program_t* program = parse_program(file);
}