#include "headers.h"
#include "cd.h"
#include "utils.h"

void cd_implementation(int parts, char *args[])
{
    if (parts >= 2)
    {
        printf("error for cd command to have more than one command-line argument \n");
        return;
    }
    char *to_dir = (char *)malloc(SZE); 
    if (parts == 0)
    {
        strcpy(to_dir, home_dir);
    }
    else
    {
        strcpy(to_dir, tilda_change(args[0]));
    }
    if (strcmp(prev_dir, "\0") == 0)
    {
        printf("error in retrieving previous directory \n");
    }
    if (strcmp(to_dir, "-") == 0)
    {
        char *display_str = (char *)malloc(SZE);
        strcpy(display_str, tilda_add(prev_dir));
        strcpy(to_dir, prev_dir);
        printf("%s \n", display_str);
        free(display_str);
    }
    getcwd(prev_dir, SZE);
    int r1 = chdir(to_dir);
    free(to_dir);
    if (r1 < 0)
    {
        printf("invalid directory: %s \n", args[0]);
        return;
    }
    return;
}