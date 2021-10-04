#include "headers.h"
#include "input.h"
#include "pipe.h"

void pipe_implementation(char *cmds)
{
    int STDOUT_FD = dup(STDOUT_FILENO);
    int STDIN_FD = dup(STDIN_FILENO);
    int switch_input = STDIN_FD;
    char *token = (char *)malloc(SZE);
    char **cmd = (char **) malloc(MINI_SZE * sizeof(char *));
    cmd[0] = (char *) malloc(MINI_SZE * sizeof(char));
    for (int i = 0; i < MINI_SZE-1; i++)
    {
        cmd[i+1] = (char *) malloc(MINI_SZE * sizeof(char));
    }
    cmd[MINI_SZE] = NULL;
    token = strtok(cmds, "|");
    int k = 0;
    while (token != NULL)
    {
        cmd[k++] = token;
        token = strtok(NULL, "|");
    }
    int fd[2];
    for (int i = 0; i < k; i++)
    {
        int r1 = 0;
        int status;
        if (i == k - 1)
        {
            // dup2(STDOUT_FD, STDOUT_FILENO);
            dup2(switch_input, STDIN_FILENO);
            parse_cmd(cmd[i]);
            // dup2(STDIN_FD, STDIN_FILENO);
            close(fd[0]);
            break;
        }
        if (pipe(fd) < 0)
        {   
            printf("pipe: unable to create pipe \n");
            return;
        }
        pid_t pid = fork();
        if (pid < 0)
        {
            printf("pipe: failed to open, terminating. \n");
            return;
        }
        if (pid == 0)
        {
            // child
            r1 = dup2(switch_input, STDIN_FILENO);
            if (r1 < 0)
            {
                printf("pipe: dup2 failed on STDIN in child \n");
                return;
            }
            r1 = dup2(fd[1], STDOUT_FILENO);
            if (r1 < 0)
            {
                printf("pipe: dup2 failed on STDIN in child \n");
                return;
            }
            close(fd[0]);
            parse_cmd(cmd[i]);
            exit(0);
        }
        else if (pid > 0)
        {
            //parent
            waitpid(pid, &status, WUNTRACED);
            close(fd[1]);
            switch_input = fd[0];
        }
    }
    int r1 = dup2(STDOUT_FD, STDOUT_FILENO);
    int r2 = dup2(STDIN_FD, STDIN_FILENO);
    if (isatty(fileno(stdin)))
        printf( "stdin is a terminal\n" );
    else
        printf( "stdin is a file or a pipe\n");
    if (r1 < 0 || r2 < 0)
    {
        printf("piping failed \n");
        PROGRAM_EXIT = -1;
        return;
    }
    return;
}