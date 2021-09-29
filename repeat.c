#include "headers.h"
#include "repeat.h"
#include "foreground.h"

// idea: use recursive function until last repeat happens
void repeat_implementation(int parts, char **args)
{
    char *buf[MINI_SZE];
    for (int i = 2; i < parts; i++)
    {
        buf[i - 2] = args[i];
    }
    if (parts <= 0)
    {
        printf("repeat: provide command \n");
        return;
    }
    for(int i = 0 ; i < strlen(args[0]) ; ++i)
    {
       if(!(args[0][i]>='0' && args[0][i]<='9'))
       {
            printf("repeat: must be followed by a number\n");
            return;
       }
    }
    for (int i = 0; i < atoi(args[0]); i++)
    {
        if (strcmp(args[1], "repeat") == 0)
        {
            repeat_implementation(parts - 2, buf);
        }
        else
        {
            foreground_implementation(parts - 2, args[1], buf);
        }
    }
    return;
}