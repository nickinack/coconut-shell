#include<stdio.h>    
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <pwd.h>
#define SZE 10000
#define MINI_SZE 1000

char home_dir[10000]; // stores the home directory
char cur_dir[10000];  // stores the current working directory
char prev_dir[10000];
int PROGRAM_EXIT;
struct proc
{
    pid_t pid;
    char *cmd;
    struct proc *next;
};
struct proc *head;
struct proc *create(pid_t pid, char *cmd);
void add(pid_t pid, char *cmd, struct proc *head);
struct proc *delete(int idx, struct proc *head);
int traverse(pid_t pid, struct proc *head);
