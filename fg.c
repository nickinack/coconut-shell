#include "headers.h"
#include "fg.h"
#include "execute_cmd.h"

void fg_implementation(int parts, char *cmd,  char *args[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("failed to initiate fork \n");
        return;
    }
    else if (pid != 0)
    {
        int wstatus;
        pid_t ppid = getpid();
        waitpid(pid, wstatus, WUNTRACED);
    }
    else if (pid == 0)
    {
        execute_cmd(parts, cmd, args);
    }
    return;
}