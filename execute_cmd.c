#include "headers.h"
#include "execute_cmd.h"

void execute_cmd(int parts, char *cmd, char *args[])
{
    char *exec_args[MINI_SZE];
    if (strcmp(args[parts-1], "&") == 0)
    {
        parts -= 1;
    }
    exec_args[0] = cmd;
    for (int i = 0; i < parts; i++)
    {
        exec_args[i + 1] = args[i];
    }
    exec_args[parts + 1] = NULL;
    for (int i = 0; i <= parts; i++)
    {
        printf("%s \n", exec_args[i]);
    }
    int r1 = execvp(cmd, exec_args);
    printf("%d \n", r1);
    return;
}