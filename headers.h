#include<stdio.h>    
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<pwd.h>
#include<signal.h>
#define SZE 10000
#define MINI_SZE 1000
#define PROMPT_COLOR "\033[1;32m"
#define DEFAULT_COLOR "\033[0m"

char home_dir[10000]; // stores the home directory
char cur_dir[10000];  // stores the current working directory
char prev_dir[10000];
int PROGRAM_EXIT;
int SKIP_SCAN;
int CUR_BG_ID;
int CUR_FG;
struct proc
{
    pid_t pid;
    char *cmd;
    int shell_id;
    int fg_cur;
    struct proc *next;
};
struct proc *head;
struct proc *create(pid_t pid, char *cmd);
struct proc *initialize_proc();
void add(pid_t pid, char *cmd, struct proc **head);
struct proc *delete(int idx, struct proc *head);
int traverse(pid_t pid, struct proc *head);
void set_val(struct proc *a, pid_t pid, char *cmd);
void print_val(struct proc *a);
void print_list(struct proc *head);
void print_jobs(struct proc *head, char flags[]);
pid_t get_pid_from_id(int id, struct proc *head);
struct proc *get_node(int idx, struct proc *head);
void kill_proc(struct proc *head);
int change_status(int idx, struct proc *head, int val);
