#include "prompt.h"
#include "headers.h"
#include "utils.h"

int get_host_user_dir_details() {

    int r1 = getlogin_r(username, SZE);
    int r2 = gethostname(hostname, SZE);
    char *r3 = (char *)malloc(MINI_SZE);
    strcpy(r3, getcwd(cur_dir, SZE));
    if (r1 != 0) 
    {
        perror("Error: while getting User name");
        PROGRAM_EXIT = 1;
        return -1;
    }
    if (r2 != 0)
    {
        perror("Error: while getting Host name");
        PROGRAM_EXIT = 1;
        return -1;
    }
    if (strcmp(r3, "\0") == 0)
    {
        perror("Error: while getting Current Working Directory");
        PROGRAM_EXIT = 1;
        return -1;
    }
    free(r3);
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
    strcat(str, tilda_add(cur_dir));
    strcat(str, ">");
    return str;
}

void prompt() {
    char* str = get_prompt();
    printf("%s%s%s ", PROMPT_COLOR, str, DEFAULT_COLOR);
    free(str);
}
