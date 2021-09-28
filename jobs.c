#include "headers.h"
#include "jobs.h"

void jobs_implementation(int parts, char **args)
{
    if (parts > 1)
    {
        printf("jobs: expected one argument but multiple arguments given \n");
        return;
    }
    char *mode = (char *)malloc(3);
    if (parts == 0)
    {
        strcpy(mode, "rs");
    }
    else if (strcmp(args[0], "-r") == 0)
    {
        strcpy(mode, "r");
    }
    else if (strcmp(args[0], "-s") == 0)
    {
        strcpy(mode, "s");
    }
    else
    {
        printf("jobs: invalid arguments \n");
        return;
    }
    print_jobs(head, mode);
    free(mode);
    return;
}