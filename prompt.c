#include "prompt.h"
#include "headers.h"

int get_host_user_dir_details() {

    int r1 = getlogin_r(username, SZE);
    int r2 = gethostname(hostname, SZE);
    char *r3 = getcwd(cur_dir, SZE);
    char *err = "-_-";
    if (r1 != 0) 
    {
        perror("Error: while getting User name");
        strcpy(username, err);
        return -1;
    }
    if(r2 != 0)
    {
        perror("Error: while getting Host name");
        strcpy(hostname, err);
        return -1;
    }
    if(strcmp(r3, "\0") == 0)
    {
        perror("Error: while getting Current Working Directory");
        strcpy(cur_dir, err);
        return -1;
    }
    return 0;
}

char* get_prompt() {
    get_host_user_dir_details();
    char *str = (char *)malloc(SZE);
    strcpy(str, "<");
    strcat(str, username);
    strcat(str, "@");
    strcat(str, hostname);
    strcat(str, ":");
    if(strstr(cur_dir, home_dir))
    {
        strcat(str, "~");
        int prompt_len = strlen(str);
        int home_dir_len = strlen(home_dir);
        int cur_dir_len = strlen(cur_dir);
        for (int i = home_dir_len; i < cur_dir_len; i++)
        {
            str[prompt_len] = cur_dir[i];
            prompt_len++;
        }
    }
    else
    {
        strcat(str, cur_dir);
    }
    strcat(str, ">");
    return str;
}

void prompt() {
    char* str = get_prompt();
    printf(PROMPT_COLOR);
    printf("%s ", str);
    printf(DEFAULT_COLOR);
}
