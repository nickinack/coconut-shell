#include "prompt.h"
#include "utils.h"
#include "input.h"
#include "headers.h"

int main()
{
    signal(SIGCHLD, sigchld_handler);
    getcwd(home_dir, SZE);
    getcwd(prev_dir, SZE);
    head = initialize_proc();
    char *cmd = "";
    set_val(head, getpid(), cmd);
    // print_val(head);
    // strcpy(head->cmd, "shell");
    while (1)
    {

        prompt();
        get_input();
        if(PROGRAM_EXIT == -1){
            break;
        }
    }
    return 0;
} 
