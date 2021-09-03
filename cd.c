#include "headers.h"
#include "cd.h"

void process_cd(int parts, char *args[]){
    if(parts > 2){
        printf("error for cd command to have more than one command-line argument \n");
        return;
    }
    if(parts <= 1){
        printf("too few arguments \n");
        return;
    }
    int r1 = chdir(args[1]);
    if(r1 < 0)
    {
        printf("invalid directory: %s \n", args[1]);
    }
    return;
}