#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

void background_implementation(int parts, char *cmd, char *args[]);