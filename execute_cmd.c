#include "headers.h"
#include "execute_cmd.h"

int execute_cmd(int parts, char *cmd, char *args[])
{
    char *exec_args[MINI_SZE];
    if (parts > 0)
    {
        if (strcmp(args[parts-1], "&") == 0)
        {
            parts -= 1;
        }
    }
    exec_args[0] = cmd;
    for (int i = 0; i < parts; i++)
    {
        exec_args[i + 1] = args[i];
    }
    exec_args[parts + 1] = NULL;
    if (execvp(cmd, exec_args) < 0)
    {
        return -1;
    }
    exit(0);
    return 0;
}
