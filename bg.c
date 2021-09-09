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
        corpse = waitpid(0, &status, WNOHANG);
        if (corpse != -1)
        {
            printf("[%s] child with pid [%d] exitted normally \n", cmd, corpse);
        }
        if (WIFEXITED(status))
        {
            printf("child exited with status of %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("child did not exit successfully \n");
        }
    }
    else if (pid == 0)
    {
        int r1 = execute_cmd(parts, cmd, args);
        if (r1 < 0)
        {
            exit(1);
        }
    }
    return;
}
