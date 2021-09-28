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
    setpgid(0, 0);
    if (pid < 0)
    {
        printf("failed to initiate fork \n");
        return;
    }
    else if (pid != 0)
    {
        pid_t ppid = getpid();
        char *full_cmd = (char *)malloc(SZE);
        strcpy(full_cmd, cmd);
        for (int i = 0; i < parts; i++)
        {
            strcat(full_cmd, " ");
            strcat(full_cmd, args[i]);
        }
        add(pid, full_cmd, &head);
        printf("child pid [%d] initiated from parent pid [%d] \n", pid, ppid);
    }
    else if (pid == 0)
    {
        int r1 = execute_cmd(parts, cmd, args);
        pid_t cpid = getpid();
        if (r1 < 0)
        {
            kill(cpid, SIGKILL);
            exit(1);
        }
    }
    return;
}

