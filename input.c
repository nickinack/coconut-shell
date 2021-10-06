#include "headers.h"
#include "input.h"
#include "cd.h"
#include "echo.h"
#include "ls.h"
#include "pwd.h"
#include "pinfo.h"
#include "foreground.h"
#include "background.h"
#include "repeat.h"
#include "history.h"
#include "dup_fd.h"
#include "jobs.h"
#include "sig.h"
#include "bg.h"
#include "fg.h"
#include "pipe.h"
#include "replay.h"

int get_input()
{
    char *buffer;
    size_t bufsize = 1;
    size_t command;
    buffer = (char *)malloc(bufsize * sizeof(char));
    int ptr = getline(&buffer, &bufsize, stdin);
    if (ptr < 0)
    {
        PROGRAM_EXIT = -1;
        return -1;
    }
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
    char *fin = (char *)malloc(MINI_SZE);
    char *fout = (char *)malloc(MINI_SZE);
    char mode;
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
        if (strlen(token) == 1 && token[0] == '>')
        {
            // output should be redirected to this file
            token = strtok(NULL, space);
            if (token == NULL)
            {
                return -1;
            }
            fout = token;
            char mode = 'n';
            CURRENT_OUT = dup_fd_out(fout, mode);
            token = strtok(NULL, space);
            continue;
        }
        else if (strlen(token) == 1 && token[0] == '<' && token[1] != '<')
        {
            // contents of this file should be redirected to input command
            token = strtok(NULL, space);
            if (token == NULL)
            {
                return -1;
            }
            fin = token;
            CURRENT_IN = dup_fd_in(fin);
            token = strtok(NULL, space);
            continue;
        }
        else if (strlen(token) == 2 && strcmp(token, ">>") == 0)
        {
            // output should be redirected and appended to this file
            token = strtok(NULL, space);
            if (token == NULL)
            {
                return -1;
            }
            fout = token;
            char mode = 'a';
            CURRENT_OUT = dup_fd_out(fout, mode);
            token = strtok(NULL, space);
            continue;
        }
        else if (strstr(token, "<<") || strstr(token, ">>>"))
        {
            printf("not valid redirection operator \n");
            return -1;
        }
        strcpy(args[k++], token);
        token = strtok(NULL, space);
    }
    args[k] = NULL;
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
        pipe_implementation(instructions[i]);
    }
    free(token);
}

void parse_cmd(char *instruction)
{
    CURRENT_IN = 0;
    CURRENT_OUT = 0;
    char **args = (char **) malloc(MINI_SZE * sizeof(char *));
    args[0] = (char *) malloc(MINI_SZE * sizeof(char));
    for (int i = 0; i < MINI_SZE-1; i++)
    {
        args[i+1] = (char *) malloc(MINI_SZE * sizeof(char));
    }
    args[MINI_SZE] = NULL;
    char *cmd = (char *)malloc(MINI_SZE);
    int parts = tokenise(instruction, args, cmd);
    if (parts == -1)
    {
        return;
    }
    if (CURRENT_IN == -1 || CURRENT_OUT == -1)
    {
        return;
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
    else if (strcmp(cmd, "jobs") == 0)
    {
        jobs_implementation(parts, args);
    }
    else if (strcmp(cmd, "sig") == 0)
    {
        sig_implementation(parts, args);
    }
    else if (strcmp(cmd, "bg") == 0)
    {
        bg_implementation(parts, args);
    }
    else if (strcmp(cmd, "fg") == 0)
    {
        fg_implementation(parts, args);
    }
    else if (strcmp(cmd, "replay") == 0)
    {
        replay_implementation(parts, args);
    }
    else if (cmd && parts >= 1 && strcmp(args[parts-1], "&") == 0)
    {
        background_implementation(parts, cmd, args);
    }
    else
    {
        foreground_implementation(parts, cmd, args);
    }
    for (int i = 0; i < MINI_SZE-1; i++)
    {
        free(args[i]);
    }
    char mode = 'i';
    restore_fd(CURRENT_IN, mode);
    mode = 'o';
    restore_fd(CURRENT_OUT, mode);
    free(args);
    free(cmd);
    return;
}
