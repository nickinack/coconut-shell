#include "headers.h"
#include "pinfo.h"
#include "utils.h"

void pinfo_implementation(int parts, char *args[])
{
    int pid = -1;
    char *dirname = (char *)malloc(SZE);
    char *fname_stat = (char *)malloc(SZE);
    char *fname_exe = (char *)malloc(SZE);
    char *buf_stat = (char *)malloc(SZE);
    char *buf_exe = (char *)malloc(SZE);
    char num_to_str[10];
    if (parts == 0)
    {
        pid = getpid();
    }
    else if (parts == 1)
    {
        pid = atoi(args[0]);
    }
    else 
    {
        printf("too many arguments for the command: pinfo \n");
        return;
    }
    sprintf(num_to_str, "%d/", pid);
    strcpy(dirname, "/proc/");
    strcat(dirname, num_to_str);
    strcpy(fname_stat, dirname);
    strcat(fname_stat, "stat");
    strcpy(fname_exe, dirname);
    strcat(fname_exe, "exe");
    struct stat dir_exists;
    if (!(stat(dirname, &dir_exists) == 0 && S_ISDIR(dir_exists.st_mode)))
    {
        printf("pinfo: invalid process id \n");
        return;
    }
    FILE *stat = fopen(fname_stat, "r");
    if(!stat)
    {
        printf("pinfo: stat file dosen't exist for the process \n");
        return;
    }
    char *process_status = (char *)malloc(2);
    char *memory = (char *)malloc(SZE);
    fgets(buf_stat, SZE, stat);
    char *token = strtok(buf_stat, " ");
    int tg_pid = 0;
    int stat_idx = 2, i = 0, mem_idx = 22, tgpid_idx=7;
    while (token != NULL)
    {
        if (i == stat_idx)
        {
            strcpy(process_status, token);
        }
        else if (i == mem_idx)
        {
            strcpy(memory, token);
        }
	else if (i == tgpid_idx)
	{
	    tg_pid = atoi(token);
	}
        token = strtok(NULL, " ");
	i++;
    }
    int r1 = readlink(fname_exe, buf_exe, SZE);
    if (r1 == -1)
    {
        printf("pinfo: cannot open exe file, permission denied \n");
        return;
    }
    if (tg_pid < 0)
    {
        printf("pinfo: error getting current foreground pid");
    }
    if (pid == tg_pid)
    {
        strcat(process_status, "+");
    }
    char *executable_path = tilda_add(buf_exe);
    printf("pid: %d\n", pid);
    printf("process status: %s\n", process_status);
    printf("memory: %s\n", memory);
    printf("executable path: %s\n", buf_exe);
    free(dirname);
    free(fname_stat);
    free(fname_exe);
    free(buf_stat);
    free(buf_exe);
    return;
}

char proc_status(pid_t pid)
{
    char *fname = (char *)malloc(MINI_SZE);
    char *buf_stat = (char *)malloc(SZE);
    int i = 0;
    char process_status = 'n';
    sprintf(fname, "/proc/%d/stat", pid);
    FILE *stat = fopen(fname, "r");
    if(!stat)
    {
        return process_status;
    }
    fgets(buf_stat, SZE, stat);
    char *token = strtok(buf_stat, " ");
    while (token != NULL)
    {
        if (i == 2)
        {
            process_status = token[0]; 
            break;       
        }
	i++;
	token = strtok(NULL, " ");
    }
    free(fname);
    free(buf_stat);
    return process_status;
}
