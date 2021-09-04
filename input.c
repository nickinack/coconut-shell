#include "input.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "headers.h"

int get_input()
{
    char *buffer;
    size_t bufsize = 1;
    size_t command;
    buffer = (char *)malloc(bufsize * sizeof(char));
    int ptr = getline(&buffer, &bufsize, stdin);
    buffer[ptr-1] = '\0';
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer \n");
        PROGRAM_EXIT = -1;
        return -2;
    }
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
    char* token = strtok(temp_buf, space);
    int k = 0;
    strcpy(cmd, token);
    token = strtok(NULL, space);
    while (token != NULL)
    {
        args[k++] = token;
        token = strtok(NULL, space);
    }
    args[k] = "\0";
    return k;
}

void process_input(char *buffer)
{   
    // tokenise, arguments
    char *args[MINI_SZE];
    char *cmd = (char *)malloc(SZE);
    int parts = tokenise(buffer, args, cmd);
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
    else
    {
        printf("command not found: %s \n", cmd);
    }
}  