#include <stdio.h>
#include <string.h>

#include "shell.h"
#include "parser.h"
#include "executor.h"
#include "builtins.h"

int main()
{
    char input[MAX_INPUT];

    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n");
            break;
        }
        //remove the enter key '/n' form the end of the input string
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        Command cmd;

        //parse the input and get the arguments like args[0] = "ls", args[1] = "-l", args[2] = NULL
        int argc = parse_input(input, &cmd);

        if (argc == 0)
            continue;

        //check if the command is a built-in command like "cd", "exit", "help"
	    if (handle_builtin(&cmd))
            continue;
        
        //execute the command using fork and execvp
        execute_command(&cmd);
    }

    return 0;
}
