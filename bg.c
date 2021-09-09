#include "headers.h"
#include "bg.h"
#include "execute_cmd.h"

// overall idea: fork, find process id
// dont wait for child process to finish
// execvp in the child process
// kill once done

void bg_implementation(int parts, char *cmd, char *args[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("failed to initiate fork \n");
        return;
    }
    else if (pid != 0)
    {
        pid_t ppid = getpid();
        printf("child pid [%d] initiated from parent pid [%d] \n", pid, ppid);
    }
    else if (pid == 0)
    {
        execute_cmd(parts, cmd, args);
    }
    return;
}