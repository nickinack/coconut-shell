#include "headers.h"
#include "fg.h"
#include "execute_cmd.h"

void fg_implemenation(int parts, char *cmd,  char *args[])
{
    execute_cmd(parts, cmd, args);
}