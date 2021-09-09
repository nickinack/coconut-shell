#include "headers.h"
#include "pinfo.h"

void pinfo_implementation(int parts, char *args[])
{
    int pid = -1;
    char *dirname = (char *)malloc(SZE);
    char *fname_stat = (char *)malloc(SZE);
    char *buf_stat = (char *)malloc(SZE);
    char num_to_str[10];
    if (parts == 1)
    {
        pid = getpid();
    }
    else if (parts == 2)
    {
        pid = atoi(args[0]);
    }
    else 
    {
        printf("too many arguments for the command: pinfo \n");
        return;
    }
    itoa(pid, num_to_str, 10);
    strcpy(dirname, "/proc/");
    strcat(dirname, num_to_str);
    strcpy(fname_stat, dirname);
    strcat(fname_stat, "stat");
    struct stat dir_exists;
    if (!(stat(dirname, &dir_exists) == 0 && S_ISDIR(dir_exists.st_mode)))
    {
        printf("pinfo: invalid process id \n");
        return;
    }
    FILE *stat = fopen(fname_stat, 'r');
    if(!stat)
    {
        printf("pinfo: stat file dosen't exist for the process");
        return;
    }
    fgets(buf_stat, SZE, stat);

}