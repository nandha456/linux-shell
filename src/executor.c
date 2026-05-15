#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "executor.h"

void execute_command(Command *cmd)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        // Input redirection
        if (cmd->input_file)
        {
            int fd = open(cmd->input_file, O_RDONLY);

            if (fd < 0)
            {
                perror("input open failed");
                exit(1);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        // Output redirection
        if (cmd->output_file)
        {
            int fd;

            if (cmd->append)
            {
                fd = open(cmd->output_file,
                          O_WRONLY | O_CREAT | O_APPEND,
                          0644);
            }
            else
            {
                fd = open(cmd->output_file,
                          O_WRONLY | O_CREAT | O_TRUNC,
                          0644);
            }

            if (fd < 0)
            {
                perror("output open failed");
                exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        execvp(cmd->args[0], cmd->args);

        perror("exec failed");
        exit(1);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}