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

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
            continue;

        char *args[MAX_ARGS];

        int argc = parse_input(input, args);

        if (argc == 0)
            continue;

	if (handle_builtin(args))
            continue;

        execute_command(args);
    }

    return 0;
}
