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
        int r1 = execute_cmd(parts, cmd, args);
        int cpid = getpid();
        if (r1 < 0)
        {
            int r2 = kill(cpid, SIGKILL);
            if (r2 < 0)
            {
                printf("%s with pid %d exitted abnormally", cmd, cpid);
                exit(1);
            }
        }
        printf("%s with pid %d exitted normally", cmd, cpid);
        exit(0);
    }
    return;
}
