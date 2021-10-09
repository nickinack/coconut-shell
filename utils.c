#include "headers.h"
#include "utils.h"
#include "prompt.h"

char *tilda_change(char *address)
{
    char *out = (char *)malloc(MINI_SZE);
    if (strcmp(address , "~") == 0)
    {
        strcpy(out, home_dir);
        return out;
    }
    else if (address[0] == '~')
    {
        strcpy(out, home_dir);
        strcat(out, address + 1);
        return out;
    }
    else
    {
        return address;
    }
}

char *tilda_add(char *address)
{
    char *out = (char *)malloc(MINI_SZE);
    if (strstr(address, home_dir))
    {
        strcpy(out, "~");
        int prompt_len = 1;
        int home_dir_len = strlen(home_dir);
        int address_len = strlen(address);
        for (int i = home_dir_len; i < address_len; i++)
        {
            out[prompt_len] = address[i];
            prompt_len++;
        }
        return out;
    }
    else
    {
        return address;
    }
}

void sigchld_handler(int sig)
{
    pid_t cpid;
    int status;
    cpid = waitpid(-1, &status, WNOHANG);
    if (cpid == -1)
    {
        return;
    }
    int idx = traverse(cpid, head);
    if (idx == -1)
    {
        return;
    }
    struct proc *bg_process = delete(idx, head);
    char *cmd = strtok(bg_process->cmd, " ");
    if (WIFEXITED(status) && bg_process->fg_cur == 0)
    {
        printf("\n[%s] command with pid [%d] ended normally \n", cmd, bg_process->pid);
        if (CUR_FG != 1)
        {
            prompt();
        }
        fflush(stdout);
    }
    else if (bg_process->fg_cur == 0)
    {
        printf("\n[%s] command with pid [%d] ended abnormally \n", cmd, bg_process->pid);
        if (CUR_FG != 1)
        {
            prompt();
        }
        fflush(stdout);
    }
    else
    {
        return;
    }
}

void sigint_handler(int signum)
{
    if (FG_RUN == 0)
    {
        printf("\n");
        prompt();
        fflush(stdout);
    }
    return;
}

void sigtstp_handler(int signum)
{
    if (FG_RUN == 0)
    {
        printf("\n");
        prompt();
        fflush(stdout);
    }
    return;
}