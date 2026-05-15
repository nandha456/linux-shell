#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT 1024
#define MAX_ARGS 64

typedef struct
{
    char *args[MAX_ARGS];

    char *input_file;
    char *output_file;

    int append;
} Command;

#endif
