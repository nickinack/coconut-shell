#include "prompt.h"
#include "headers.h"

int main()
{
    getcwd(home_dir, SZE);
    while (1)
    {
        prompt();
        char a[100];
        scanf("%s", a);
        if(strcmp(a, "exit") == 0){
            return 0;
        }
    }
}
