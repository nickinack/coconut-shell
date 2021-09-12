#include "headers.h"
#include "input.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "pinfo.h"
#include "bg.h"
#include "fg.h"
#include "repeat.h"
#include "history.h"

int get_input()
{
    char *buffer;
    size_t bufsize = 1;
    size_t command;
    buffer = (char *)malloc(bufsize * sizeof(char));
    int ptr = getline(&buffer, &bufsize, stdin);
    buffer[ptr] = '\0';
    history_implementation(buffer);
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer \n");
        PROGRAM_EXIT = -1;
        return -2;
    }
    buffer[ptr-1] = '\0';
    if (strcmp(buffer, "exit") == 0)
    {
        printf("Exiting the shell .... \n");
        PROGRAM_EXIT = -1;
        return -1;
    }
    process_input(buffer);
    return 0;
}

int tokenise(char *buffer, char **args, char *cmd)
{
    char space[MINI_SZE] = " \n\t\r";
    char temp_buf[SZE];
    strcpy(temp_buf, buffer);
    char *token = strtok(temp_buf, space);
    if (token == NULL)
    {
        return -1;
    }
    int k = 0;
    strcpy(cmd, token);
    token = strtok(NULL, space);
    while (token != NULL)
    {
        args[k++] = token;
        token = strtok(NULL, space);
    }
    args[k] = "\0";
    free(token);
    return k;
}

void process_input(char *buffer)
{
    // tokenise, arguments
    char colon[MINI_SZE] = ";";
    char *token = strtok(buffer, ";");
    char *instructions[MINI_SZE];
    int k = 0;
    while (token != NULL)
    {
        //tokenise(token, args, cmd);
        instructions[k++] = token;
        token = strtok(NULL, ";");
    }
    for (int i = 0; i < k; i++)
    {
        char *args[MINI_SZE];
        char *cmd = (char *)malloc(MINI_SZE);
        int parts = tokenise(instructions[i], args, cmd);
        if (parts == -1)
        {
            continue;
        }
        if (strcmp(cmd, "cd") == 0)
        {
            cd_implementation(parts, args);
        }
        else if (strcmp(cmd, "ls") == 0)
        {
            ls_implementation(parts, args);
        }
        else if (strcmp(cmd, "echo") == 0)
        {
            echo_implementation(parts, args);
        }
        else if (strcmp(cmd, "pwd") == 0)
        {
            pwd_implementation(parts, args);
        }
        else if (strcmp(cmd, "pinfo") == 0)
        {
            pinfo_implementation(parts, args);
        }
        else if (strcmp(cmd, "repeat") == 0)
        {
            repeat_implementation(parts, args);
        }
        else if (strcmp(cmd, "history") == 0)
        {
            history_handle(parts, args);
        }
        else if (cmd && parts >= 1 && strcmp(args[parts-1], "&") == 0)
        {
            bg_implementation(parts, cmd, args);
        }
        else
        {
            fg_implementation(parts, cmd, args);
        }
        free(cmd);
    }
}
