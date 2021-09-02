#include "prompt.h"
#include "input.h"
#include "headers.h"

int main()
{
    getcwd(home_dir, SZE);
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
