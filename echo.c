#include "headers.h"
#include "echo.h"

void echo_implementation(int parts, char ** args)
{
    for (int i = 0; i < parts; i++)
    {
        printf("%s ", args[i]);
    }
    printf("\n");
}