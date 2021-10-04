#include "headers.h"
#include "dup_fd.h"

int dup_fd_out(char *fname, char mode)
{
    int fd; 
    if (mode == 'n')
    {
        fd = open(fname, O_CREAT | O_RDWR | O_TRUNC, 0644);
    }
    else
    {
        fd = open(fname, O_CREAT | O_RDWR | O_APPEND, 0644);
    }
    if (fd < 0)
    {
        printf("> invalid filename \n");
        return -1;
    }
    int restore_fd = dup(STDOUT_FILENO);
    if (restore_fd < 0)
    {
        printf("> redirection error \n");
        return -1;
    }
    int cur_fd = dup2(fd, STDOUT_FILENO);
    if (cur_fd < 0)
    {
        printf("> redirection error \n");
        return -1;
    }
    return restore_fd;
}
int dup_fd_in(char *fname)
{
    int fd = open(fname, O_CREAT | O_RDWR);
    if (fd < 0)
    {
        printf("< invalid filename \n");
        return -1;
    }
    int restore_fd = dup(STDIN_FILENO);
    if (restore_fd < 0)
    {
        printf("< redirection error \n");
        return -1;
    }
    int cur_fd = dup2(fd, STDIN_FILENO);
    if (cur_fd < 0)
    {
        printf("< redirection error \n");
        return -1;
    }
    return restore_fd;

}
int restore_fd(int fd, char mode)
{
    int r1;
    if (fd <= 0)
    {
        return fd;
    }
    if (mode == 'o')
    {
        r1 = dup2(fd, STDOUT_FILENO);
    }
    else
    {
        r1 = dup2(fd, STDIN_FILENO);
    }
    if (r1 < 0)
    {
        printf("< restore error \n");
        return -1;
    }
    close(fd);
    return r1;
}