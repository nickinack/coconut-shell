#include "headers.h"

struct proc *create(pid_t pid, char *cmd)
{
    struct proc *new_node = malloc(sizeof(struct proc));
    new_node->pid = pid;
    strcpy(new_node->cmd, cmd);
    new_node->next = NULL;
    return new_node;
}

void add(pid_t pid, char *cmd, struct proc *head)
{
    struct proc *cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = malloc(sizeof(struct proc));
    cur->next->pid = pid;
    strcpy(cur->next->cmd, cmd);
    cur->next->next = NULL;
    return;
}

struct proc *delete(int idx, struct proc *head)
{
    struct proc *ret;
    ret->next = NULL;
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
    ret = temp;
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
    while (cur->next != NULL)
    {
        if (cur->pid == pid)
        {
            return i;
        }
        if (cur->next == NULL)
        {
            return -1;
        }
        i++;
    }
    return -1;
}