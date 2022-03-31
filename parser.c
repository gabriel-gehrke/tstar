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
            // read next character in stream, skip if whitespace
            c = fgetc(stream);
            if (c != ' ' && c != '\t' && c != EOF)
            {
                buff[i++] = c;
            }
        } while (c != EOF && c != '\n' && i < MAX_LINE_LENGTH);

        if (i == MAX_LINE_LENGTH)
        {
            THROW("The maximum line length was breached");
        }
        buff[i] = 0;

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
    //printf("- %lu -\n", strlen(token));
    puts(token);
    if (strlen(token) != 5) return false;

    // get opcode
    {
        const char v[3] = {token[0], token[1], 0};
        out->opcode = (opcode_t) (uint) strtoul(v, NULL, 10);
        if (out->opcode == 0 && strcmp(v, "00") != 0) return false;
    }

    // get param
    {
        const char v[4] = {token[2], token[3], token[4], 0};
        out->param = (ushort) strtoul(v, NULL, 10);
        if (out->param == 0 && strcmp(v, "000") != 0) return false;
    }

    printf("opcode: %u\n", out->opcode);
    printf("param : %u\n", out->param);

    return true;
}
