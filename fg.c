#include "utils.h"

void fg_implementation(int parts, char *cmd,  char *args[])
{
    signal(SIGTTOU, SIG_IGN);
    setpgid(0, 0);
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
        tcsetpgrp(0, pid);
        waitpid(pid, &wstatus, WUNTRACED);
        tcsetpgrp(0, ppid);
        signal(SIGTTOU, SIG_DFL);
    }
    else if (pid == 0)
    {
        printf("%d \n", getpid());
        execute_cmd(parts, cmd, args);
    }
    return;
}
