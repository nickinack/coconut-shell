#include "headers.h"
#include "utils.h"

char *tilda_change(char *address)
{
    char *out = (char *)malloc(MINI_SZE);
    if (strcmp(address , "~") == 0)
    {
        strcpy(out, home_dir);
        return out;
    }
    else if (address[0] == '~')
    {
        strcpy(out, home_dir);
        strcat(out, address + 1);
        return out;
    }
    else
    {
        return address;
    }
}

char *tilda_add(char *address)
{
    char *out = (char *)malloc(MINI_SZE);
    if (strstr(address, home_dir))
    {
        strcpy(out, "~");
        int prompt_len = 1;
        int home_dir_len = strlen(home_dir);
        int address_len = strlen(address);
        for (int i = home_dir_len; i < address_len; i++)
        {
            out[prompt_len] = address[i];
            prompt_len++;
        }
        return out;
    }
    else
    {
        return address;
    }
}