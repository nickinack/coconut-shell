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
        int status;
        pid_t corpse;
        while(corpse = waitpid(0, &status, WNOHANG) != -1)
        {
            //do
        }
        if (corpse == -1)
        {
            printf("error");
        }
        if (WIFEXITED(status) == -1)
        {
            printf("\n[%s] child with pid [%d] exitted abnormally \n", cmd, getpid());
        }
        else if (WIFEXITED(status) == 0)
        {
            printf("\n[%s] child with pid [%d] exitted normally \n", cmd, getpid());
        }
    }
    else if (pid == 0)
    {
        int r1 = execute_cmd(parts, cmd, args);
        if (r1 < 0)
        {
            exit(-1);
        }
    }
    return;
}
