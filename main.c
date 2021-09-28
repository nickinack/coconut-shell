#include "headers.h"
#include "prompt.h"
#include "utils.h"
#include "input.h"
#include "history.h"

int main()
{
    signal(SIGCHLD, sigchld_handler);
    getcwd(home_dir, SZE);
    getcwd(prev_dir, SZE);
    head = initialize_proc();
    hist_size = 0;
    initialize(history);
    char *cmd = "";
    set_val(head, getpid(), cmd);
    hname = (char *)malloc(MINI_SZE);
    set_hpath(hname);
    retrieve_history();
    CUR_BG_ID = 0;
    // print_val(head);
    // strcpy(head->cmd, "shell");
    while (1)
    {
        char *flags = "rs";
        print_jobs(head, flags);
        prompt();
        get_input();
        if(PROGRAM_EXIT == -1){
            return 0;
        }
    }
    return 0;
} 
