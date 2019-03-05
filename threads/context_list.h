//POSIX -- allows for using the sigjmp_buf structure
//#define _POSIX_SOURCE 

#ifndef CONTEXT_LIST_H
#define CONTEXT_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdbool.h>

struct node
{
    bool completed;
    int thread_id;
    int ticket_count;
    int work_amount;
    int quantum;
    int value;
    int work_units;
    char *stack;

    sigjmp_buf env;

    struct node *next;
    
};
typedef struct node node;

struct context_list
{
    node *head;
    node *tail;
    unsigned int count;
};
typedef struct  context_list context_list;

context_list * context_list_create();
void context_list_empty(context_list *list);
void context_list_add_tail(context_list *list, node *data);
void context_list_add_head(context_list *list, node *data);
unsigned int context_list_get_count(const context_list *list);

#endif