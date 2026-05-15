/*
 * shell_parser.c
 * Complete example: parse a shell-like command string into a Command struct
 * Compile: gcc -Wall -Wextra -o shell_parser shell_parser.c
 * Run:     ./shell_parser "ls -la /tmp > out.txt"
 */

#include <string.h>

#include "parser.h"

// parse_input: Tokenizes a shell-like command string in-place and fills a Command struct.
// Returns the number of arguments parsed (argc).
// ⚠️ WARNING: This function MODIFIES the 'input' string by inserting '\0' to split tokens.
// ⚠️ All pointers in 'cmd' (args[], input_file, output_file) point INTO the 'input' buffer.
// ⚠️ The 'input' buffer must remain valid and mutable for the lifetime of the 'cmd' struct.
int parse_input(char *input, Command *cmd)
{
    int argc = 0;  // Counter for number of arguments parsed

    char *p = input;  // Working pointer to traverse the input string

    // Initialize redirection fields to safe defaults
    cmd->input_file = NULL;   // No input redirection by default
    cmd->output_file = NULL;  // No output redirection by default
    cmd->append = 0;          // Default: overwrite mode (>) not append (>>)

    // Main parsing loop: continue until we hit the null terminator
    while (*p)
    {
        // Skip any leading whitespace (spaces or tabs) before the next token
        while (*p == ' ' || *p == '\t')
            p++;

        // If we've reached the end after skipping whitespace, exit loop
        if (*p == '\0')
            break;

        // ─────────────────────────────────────────────────────────────
        // Handle Output Redirection: > file  or  >> file
        // ─────────────────────────────────────────────────────────────
        if (*p == '>')
        {
            p++;  // Move past the first '>'

            // Check for append mode: >>
            if (*p == '>')
            {
                cmd->append = 1;  // Set append flag
                p++;              // Move past the second '>'
            }

            // Skip whitespace between '>>' and the filename
            while (*p == ' ' || *p == '\t')
                p++;

            // Mark the start of the output filename (pointer into input buffer)
            cmd->output_file = p;

            // Advance p to the end of the filename (stop at whitespace or end)
            while (*p && *p != ' ' && *p != '\t')
                p++;

            // NULL-terminate the filename by overwriting the delimiter with '\0'
            if (*p)
            {
                *p = '\0';  // 🔥 This modifies the original input string!
                p++;        // Move past the null terminator for next token
            }

            continue;  // Skip to next iteration (filename is not an arg)
        }

        // ─────────────────────────────────────────────────────────────
        // Handle Input Redirection: < file
        // ─────────────────────────────────────────────────────────────
        if (*p == '<')
        {
            p++;  // Move past '<'

            // Skip whitespace between '<' and the filename
            while (*p == ' ' || *p == '\t')
                p++;

            // Mark the start of the input filename (pointer into input buffer)
            cmd->input_file = p;

            // Advance p to the end of the filename
            while (*p && *p != ' ' && *p != '\t')
                p++;

            // NULL-terminate the filename
            if (*p)
            {
                *p = '\0';  // 🔥 Modifies original input string
                p++;
            }

            continue;  // Skip to next iteration (filename is not an arg)
        }

        // ─────────────────────────────────────────────────────────────
        // Handle Quoted Arguments: "hello world" or 'hello world'
        // ─────────────────────────────────────────────────────────────
        if (*p == '"' || *p == '\'')
        {
            char quote = *p;  // Remember which quote character opened this
            p++;              // Move past the opening quote

            // Mark start of argument (after the quote)
            cmd->args[argc++] = p;

            // Find the closing quote
            while (*p && *p != quote)
                p++;

            // NULL-terminate at the closing quote position
            if (*p)
            {
                *p = '\0';  // 🔥 Replaces closing quote with '\0'
                p++;        // Move past it
            }
            // Note: The opening quote was skipped, so args[i] points to content only
        }
        // ─────────────────────────────────────────────────────────────
        // Handle Normal (Unquoted) Arguments
        // ─────────────────────────────────────────────────────────────
        else
        {
            // Mark start of this argument token
            cmd->args[argc++] = p;

            // Advance p until we hit a delimiter: space, tab, <, or >
            while (*p && *p != ' ' &&
                   *p != '\t' &&
                   *p != '<' &&
                   *p != '>')
            {
                p++;
            }

            // NULL-terminate the token at the delimiter position
            if (*p)
            {
                *p = '\0';  // 🔥 Replaces delimiter with '\0'
                p++;        // Move past it for next token
            }
        }
    }

    // CRITICAL: NULL-terminate the args array so execvp() knows where it ends
    cmd->args[argc] = NULL;

    // Return the count of arguments parsed (useful for debugging or validation)
    return argc;
}