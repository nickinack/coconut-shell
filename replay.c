#include "headers.h"
#include "replay.h"
#include "pipe.h"

void replay_implementation(int parts, char **args)
{
    if (parts < 5)
    {
        printf("replay: not enough arguments \n");
        return;
    }
    int period = -1, interval = -1;
    int k = 0; 
    char *cmd = (char *)malloc(MINI_SZE);
    strcpy(cmd, "");
    for (int i = 0; i < parts; i++)
    {
        if (strcmp(args[i], "-interval") == 0 && args[i + 1] != NULL)
        {
            interval = atoi(args[i + 1]);
        }
        else if (strcmp(args[i], "-period") == 0 && args[i + 1] != NULL)
        {
            period = atoi(args[i + 1]);
        }
        else if (strcmp(args[i], "-command") == 0 && args[i + 1] != NULL)
        {
            for (int j = i + 1; j < parts; j++)
            {
                if (strcmp(args[j], "-interval") == 0 || strcmp(args[j], "-period") == 0)
                {
                    break;
                }
                strcat(cmd, args[j]);
                strcat(cmd, " ");
            }
        }
    }
    while (period - interval >= 0)
    {
        char *sleep_cmd = (char *)malloc(MINI_SZE);
        char *seconds = (char *)malloc(10);
        strcpy(sleep_cmd, "sleep");
        strcat(sleep_cmd, " ");
        sprintf(seconds, "%d", interval);   
        strcat(sleep_cmd, seconds);
        pipe_implementation(sleep_cmd);
        pipe_implementation(cmd);
        period -= interval;
    }
    // printf("command: %s \n", cmd);
}

