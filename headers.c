#include "headers.h"
#include "pinfo.h"

struct proc *create(pid_t pid, char *cmd)
{
    struct proc *new_node = malloc(sizeof(struct proc));
    new_node->pid = pid;
    strcpy(new_node->cmd, cmd);
    new_node->next = NULL;
    new_node->fg_cur = 0;
    return new_node;
}

int compare_jobs(struct proc *a, struct proc *b) {
     return strcmp(a->cmd, b->cmd);
}

void add(pid_t pid, char *cmd, struct proc **head)
{
    // lexicographical addition
    struct proc *new_node = initialize_proc();
    new_node->pid = pid;
    new_node->shell_id = CUR_BG_ID++;
    strcpy(new_node->cmd, cmd);
    if (head == NULL || compare_jobs(new_node, *head) < 0) {
        new_node->next = *head;
        return;
    }
    struct proc *cur = *head;
    while (cur->next != NULL && compare_jobs(new_node, cur->next) >= 0)
    {
        cur = cur->next;
    }
    new_node->next = cur->next;
    cur->next = new_node;
    return;
}

struct proc *delete(int idx, struct proc *head)
{

    struct proc *ret = initialize_proc();
    ret->pid = -1;
    ret->shell_id = -1;
    if (head == NULL)
    {
        return ret;
    }
    if (idx == 0)
    {
        return ret;
    }
    struct proc *cur = head;
    struct proc *temp = head;
    for (int i = 0; i < idx - 1; i++)
    {
        if (cur->next == NULL)
        {
            return ret;
        }
        cur = cur->next;
    }
    temp = cur->next;
    ret->pid = temp->pid;
    strcpy(ret->cmd, temp->cmd);
    ret->fg_cur = temp->fg_cur;
    cur->next = temp->next;
    free(temp);
    return ret;
}

struct proc *get_node(int idx, struct proc *head)
{

    struct proc *ret = initialize_proc();
    ret->pid = -1;
    ret->shell_id = -1;
    if (head == NULL)
    {
        return ret;
    }
    if (idx == 0)
    {
        return ret;
    }
    struct proc *cur = head;
    for (int i = 0; i < idx; i++)
    {
        if (cur->next == NULL)
        {
            return cur;
        }
        cur = cur->next;
    }
    return cur;
}

int traverse(pid_t pid, struct proc *head)
{
    int i = 0;
    if (head == NULL)
    {
        return -1;
    }
    struct proc *cur = head;
    while (cur != NULL)
    {
        if (cur->pid == pid)
        {
            return i;
        }
        if (cur->next == NULL)
        {
            return -1;
        }
        cur = cur->next;
        i++;
    }
    return -1;
}

int change_status(int idx, struct proc *head, int val)
{
    if (val < 0 || val > 1)
    {
        return -1;
    }
    if (head == NULL)
    {
        return -1;
    }
    if (idx == 0)
    {
        return -1;
    }
    struct proc *cur = head;
    for (int i = 0; i < idx; i++)
    {
        if (cur->next == NULL)
        {
            return -1;
        }
        cur = cur->next;
    }
    cur->fg_cur = val;
    printf("[%d] status changed \n", cur->pid);
    return 0;
}

pid_t get_pid_from_id(int id, struct proc *head)
{
    int i = 0;
    if (head == NULL)
    {
        return -1;
    }
    struct proc *cur = head;
    while (cur != NULL)
    {
        if (cur->shell_id == id)
        {
            return cur->pid;
        }
        if (cur->next == NULL)
        {
            return -1;
        }
        cur = cur->next;
        i++;
    }
    return -1;
}

struct proc *initialize_proc()
{
    struct proc *a = malloc(sizeof(struct proc));
    a->pid = 0;
    a->cmd = (char *)malloc(MINI_SZE);
    a->shell_id = -1;
    a->next = NULL;
    a->fg_cur = 0;
    return a;
}

void set_val(struct proc *a, pid_t pid, char *cmd)
{
    a->pid = pid;
    strcpy(a->cmd, cmd);
}

void print_val(struct proc *a)
{
    printf("pid: %d \n", a->pid);
    printf("cmd: %s \n", a->cmd);
}

void print_list(struct proc *head)
{
    struct proc *cur = head;
    while (cur != NULL)
    {
        printf("%d \n", cur->pid);
        cur = cur->next;
    }
    return;
}

void print_jobs(struct proc *head, char flags[])
{
    struct proc *cur = head;
    cur = cur->next;
    while (cur != NULL)
    {
        if (cur->fg_cur == 1)
        {
            cur = cur->next;
            continue;
        }
        char stat = proc_status(cur->pid);
        char *stat_word = (stat == 'T' ? "Stopped" : stat == 'n' ? "Stopped": "Running");
        if (strlen(flags) == 2)
        {
            printf("[%d] %s %s [%d] \n", cur->shell_id, stat_word, cur->cmd, cur->pid);
        }
        else if ((flags[0] == 'r') && strcmp(stat_word, "Running") == 0)
        {
            printf("[%d] %s %s [%d] \n", cur->shell_id, stat_word, cur->cmd, cur->pid);
        }
        else if (flags[0] == 's' && strcmp(stat_word, "Stopped") == 0)
        {
            printf("[%d] %s %s [%d] \n", cur->shell_id, stat_word, cur->cmd, cur->pid);
        }
        cur = cur->next;
    }
    return;
}

void kill_proc(struct proc *head)
{
    int i = 0;
    if (head == NULL)
    {
        return;
    }
    struct proc *cur = head;
    cur = cur->next;
    while (cur != NULL)
    {
        kill(cur->pid, SIGKILL);
        cur = cur->next;
        i++;
    }
    exit(0);
    return;
}
