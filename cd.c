#include "headers.h"
#include "cd.h"

void process_cd(int parts, char *args[]){
    if (parts > 2)
    {
        printf("error for cd command to have more than one command-line argument \n");
        return;
    }
    if (parts <= 1)
    {
        printf("too few arguments \n");
        return;
    }
    if (strcmp(prev_dir, "\0") == 0)
    {
        printf("error in retrieving previous directory \n");
    }
    char *to_dir = (char *)malloc(SZE); 
    strcpy(to_dir, args[1]);
    if (strcmp(to_dir, "-") == 0)
    {
        char *display_str = (char *)malloc(SZE);
        if (strstr(prev_dir, home_dir))
        {
            strcat(display_str, "~");
            int prompt_len = strlen(display_str);
            int home_dir_len = strlen(home_dir);
            int prev_dir_len = strlen(prev_dir);
            for (int i = home_dir_len; i < prev_dir_len; i++)
            {
                display_str[prompt_len] = prev_dir[i];
                prompt_len++;
            }
        }
        else
        {
            strcpy(display_str, prev_dir);
        }
        strcpy(to_dir, prev_dir);
        printf("%s \n", display_str);
    }
    if(strcmp(to_dir, "~") == 0)
    {
        strcpy(to_dir, home_dir);
    }
    getcwd(prev_dir, SZE);
    int r1 = chdir(to_dir);
    if (r1 < 0)
    {
        printf("invalid directory: %s \n", args[1]);
        return;
    }
    return;
}