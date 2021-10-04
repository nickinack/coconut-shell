#include "headers.h"
#include "fg.h"

void fg_implementation(int parts, char **args)
{
    if (parts > 1)
    {
        printf("fg: too many arguments \n");
        return;
    }
    if (parts < 1)
    {
        printf("fg: too few arguments \n");
        return;
    }
    int proc_shell_id = atoi(args[0]);
    if (proc_shell_id < 0)
    {
        printf("fg: invalid proc shell id \n");
        return;
    }
    pid_t pid = get_pid_from_id(proc_shell_id, head);
    if (pid == -1)
    {
        printf("fg: no process running for the given shell id \n");
        return;
    }
    // give terminal control to the background process.
    int status = 0;
    pid_t shell_pid = getpgid(0);
    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, pid);
    kill(pid, SIGCONT);
    CUR_FG = 1;
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, shell_pid);
    signal(SIGTTOU, SIG_DFL);
    int idx = traverse(pid, head);
    if (idx != -1)
    {
        delete (idx, head);
    }
    if (WIFSTOPPED(status))
    {
        printf("fg: process with pid [%d] has suspended normally \n", pid);
    }
    return;
}