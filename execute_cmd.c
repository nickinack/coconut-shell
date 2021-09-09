#include "headers.h"
#include "execute_cmd.h"

int execute_cmd(int parts, char *cmd, char *args[])
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
    int r1 = execvp(cmd, exec_args);
    if (r1 < 0)
    {
        printf("command failed with return value 1 \n");
        return -1;
    }
    printf("done! \n");
    return 0;
}
