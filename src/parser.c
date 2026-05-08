#include <stdio.h>
#include "parser.h"

int parse_input(char *input, char *args[])
{
    int argc = 0;
    char *p = input;

    while (*p)
    {
        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '\0')
            break;

        if (*p == '"' || *p == '\'')
        {
            char quote = *p;
            p++;

            args[argc++] = p;

            while (*p && *p != quote)
                p++;

            if (*p)
            {
                *p = '\0';
                p++;
            }
        }
        else
        {
            args[argc++] = p;

            while (*p && *p != ' ' && *p != '\t')
                p++;

            if (*p)
            {
                *p = '\0';
                p++;
            }
        }
    }

    args[argc] = NULL;

    return argc;
}
