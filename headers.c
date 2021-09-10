#include "headers.h"

struct proc *create(pid_t pid, char *cmd)
{
    struct proc *new_node = malloc(sizeof(struct proc));
    new_node->pid = pid;
    strcpy(new_node->cmd, cmd);
    new_node->next = NULL;
    return new_node;
}

void add(pid_t pid, char *cmd, struct proc **head)
{
    struct proc *cur = *head;
    struct proc *new_node = initialize_proc();
    new_node->pid = pid;
    strcpy(new_node->cmd, cmd);
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = new_node;
    return;
}

struct proc *delete(int idx, struct proc *head)
{

    struct proc *ret = initialize_proc();
    ret->pid = -1;
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
    cur->next = temp->next;
    free(temp);
    return ret;
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

struct proc *initialize_proc()
{
    struct proc *a = malloc(sizeof(struct proc));
    a->pid = 0;
    a->cmd = (char *)malloc(MINI_SZE);
    a->next = NULL;
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
