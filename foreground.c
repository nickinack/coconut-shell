#include "headers.h"
#include "foreground.h"
#include "utils.h"
#include "execute_cmd.h"

void foreground_implementation(int parts, char *cmd,  char *args[])
{
    signal(SIGTTOU, SIG_IGN);
    // setpgid(0, 0);
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
        waitpid(pid, &wstatus, WUNTRACED);
        tcsetpgrp(0, ppid);
        signal(SIGTTOU, SIG_DFL);
        if (WIFSTOPPED(wstatus))
        {
            //process has gone to background to Ctrl+Z trigger
            char *full_cmd = (char *)malloc(SZE);
            strcpy(full_cmd, cmd);
            for (int i = 0; i < parts; i++)
            {
                strcat(full_cmd, " ");
                strcat(full_cmd, args[i]);
            }
            add(pid, full_cmd, &head);
            printf("process with pid [%d] has started in background \n", pid);
            return;
        }
    }
    else if (pid == 0)
    {
        // printf("%d \n", getpid());
        tcsetpgrp(0, pid);
        signal(SIGTTOU, SIG_DFL);
        int r1 = execute_cmd(parts, cmd, args);
        if (r1 < 0)
        {
            exit(1);
        }
        exit(0);
    }
    return;
}
