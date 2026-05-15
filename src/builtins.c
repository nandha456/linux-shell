#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"


int handle_builtin(Command *cmd)
{
    if (cmd->args[0] == NULL)
        return 1;

    // exit command
    if (strcmp(cmd->args[0], "exit") == 0)
    {
        printf("Exiting shell...\n");
        exit(0);
    }

    // cd command
    if (strcmp(cmd->args[0], "cd") == 0)
    {
        if (cmd->args[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        else
        {
            if (chdir(cmd->args[1]) != 0)
            {
                perror("cd failed");
            }
        }

        return 1;
    }

    return 0;
}
