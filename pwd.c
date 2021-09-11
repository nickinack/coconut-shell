#include "headers.h"
#include "pwd.h"

void pwd_implementation(int parts, char **args)
{
    if(parts > 0)
    {
        printf("pwd: too many arguments \n");
    }
    char *pwd = (char *)malloc(SZE);
    int buf_size = SZE;
    pwd = getcwd(pwd, buf_size);
    if(strcmp(pwd, "\0") == 0)
    {
        printf("getcwd() error \n");
        return;
    }
    printf("%s \n", pwd);
    free(pwd);
    return;
}