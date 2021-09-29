#include "headers.h"
#include "bg.h"

void bg_implementation(int parts, char **args)
{
    if (parts > 1)
    {
        printf("bg: too many arguments \n");
        return;
    }
    if (parts < 1)
    {
        printf("bg: too few arguments \n");
        return;
    }
    int proc_shell_id = atoi(args[0]);
    if (proc_shell_id < 0)
    {
        printf("bg: invalid proc shell id \n");
        return;
    }
    pid_t pid = get_pid_from_id(proc_shell_id, head);
    if (pid == -1)
    {
        printf("bg: no process running for the given shell id \n");
        return;
    }
    int r1 = kill(pid, SIGCONT); // Changes the state of process to running (in the # background).
    if (r1 < 0)
    {
        printf("bg: error changing state of the process \n");
        return;
    }
    else
    {
        printf("bg: state of the process changes successfully \n");
    }
    return;
}