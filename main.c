#include "headers.h"
#include "prompt.h"
#include "utils.h"
#include "input.h"
#include "history.h"

int main()
{
    CUR_FG = -1;
    FG_RUN = 0;
    signal(SIGCHLD, sigchld_handler);
    signal(SIGINT, sigint_handler);
    signal(SIGTSTP, sigtstp_handler);
    getcwd(home_dir, SZE);
    getcwd(prev_dir, SZE);
    head = initialize_proc();
    head->pid = getpid();
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
        prompt();
        get_input();
        if(PROGRAM_EXIT == -1){
            printf("killing bg ... \n");
            kill_proc(head);
            return 0;
        }
    }
    return 0;
} 
