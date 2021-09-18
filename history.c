#include "headers.h"
#include "history.h"

void set_hpath(char *hname)
{
    strcpy(hname, home_dir);
    strcat(hname, "/");
    strcat(hname, "history.txt");
}
void history_implementation(char *cmd)
{
    retrieve_history();
    append_entry(cmd);
    write_to_file();
    return;
}
void initialize(char *history[30])
{
    for (int i = 0; i < 30; i++)
    {
        history[i] = (char *)malloc(MINI_SZE);
    }
}
void append_entry(char *cmd)
{
    cmd[strlen(cmd) - 1] = '\0';
    if (strcmp(cmd, "\0") == 0 || strcmp(cmd, "/n") == 0 || cmd[0] == 10)
    {
        return;
    }
    if (hist_size > 19)
    {
        hist_size = 19;
    }
    for (int i = hist_size; i > 0; i--)
    {
        strcpy(history[i], history[i - 1]);
    }
    strcpy(history[0], cmd);
    hist_size++;
    return;
}
void write_to_file()
{
    FILE *fp;
    fp = fopen(hname, "w");
    int i = 0;
    while (i < hist_size)
    {
        fprintf(fp, "%s\n", history[i]);
        i++;
    }
    fclose(fp);
    return;
}
void retrieve_history()
{
    hist_size = 0;
    FILE *fp;
    fp = fopen(hname, "r");
    char buf[SZE];
    while (fgets(buf, sizeof(buf), fp) != NULL)
    {
        buf[strlen(buf)-1] = '\0';
        // printf("%s %d \n", buf, strlen(buf));
        strcpy(history[hist_size], buf);
        hist_size++;
    }
    fclose(fp);
    return;
}
void print_history(int num)
{
    int i = 0;
    while (i < num)
    {
        printf("%s \n", history[num-i-1]);
        i++;
    }
    return;
}
void history_handle(int parts, char **args)
{
    if (parts > 1)
    {
        printf("history: wrong number of args \n");
        return;
    }
    int num;
    if (parts == 0)
    {
        num = 10;
    }
    else
    {
        num = atoi(args[0]);
    }
    print_history(num);
}