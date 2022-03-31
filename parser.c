#include "parser.h"
#include "string.h"

#define START_CAP 100
#define MAX_LINE_LENGTH ((5 * 5) + 5 + 1)

#define THROW(msg) fprintf(stderr, "Line %d: %s.\n", lineno, msg); exit(1); 

program_t* parse_program(FILE* stream)
{
    program_t* p = program_allocate(START_CAP);

    uint lineno = 1;
    char buff[MAX_LINE_LENGTH];

    while (!feof(stream))
    {
        program_ensure_capacity(p, lineno);

        operation_t* op = &p->operations[p->length++];

    	// read a line into the buffer
        uint i = 0;
        char c;
        do
        {
            c = fgetc(stream);
            buff[i++] = c;
            //putc(c, stdout);
            putc((c != '\n' && i < MAX_LINE_LENGTH) + '0', stdout);
            putc('\n', stdout);
        } while (!feof(stream) && c != '\n' && i < MAX_LINE_LENGTH);

        if (i == MAX_LINE_LENGTH)
        {
            THROW("The maximum line length was breached");
        }

        if (!parse_line(buff, &p->operations[p->length++]))
        {
            THROW("Error during parsing the line");
        }

        lineno++;
    }

    return p;
}

bool parse_line(const char* s, operation_t* out)
{
    char buff[strlen(s) + 1];
    strcpy(buff, s);

    char* token = strtok(buff, ",");
    if (!token) return false;

    // get opcode
    {
        const char v[3] = {token[0], token[1], 0};
        out->opcode = (opcode_t) (uint) strtoul(v, NULL, 10);
        if (out->opcode == 0 && strcmp(v, "00") != 0) return false;
    }

    // get param
    {
        const char v[4] = {token[2], token[3], token[4], 0};
        out->param = (ushort) strtoul(s, NULL, 10);
        if (out->param == 0 && strcmp(v, "000") != 0) return false;
    }

    return true;
}
