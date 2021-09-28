#include "headers.h"
#include "sig.h"

void sig_implementation(int parts, char **args)
{
    if (parts > 2)
    {
        printf("sig: incorrect number of arguments \n");
        return;
    }
    int procid = atoi(args[0]);
    if (procid < 0)
    {
        printf("sig: expected a positive process id \n");
        return;
    }
    pid_t pid = get_pid_from_id(procid, head);
    if (pid == -1)
    {
        printf("sig: no such process exists \n");
        return;
    }
    int signum = atoi(args[1]);
    if (signum < 0)
    {
        printf("sig: expected a positive signal id \n");
        return;
    }
    int r1 = kill(pid, signum);
    if (r1 < 0)
    {
        printf("sig: not able to send signal \n");
        return;
    }
    else
    {
        printf("signal sent to process with pid [%d] successfully \n", pid);
    }
    return;
}