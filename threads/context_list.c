/*
*   ITCR -- SOA -- Proyecto 1.
*   Loteria de threads.
*   Acuna-Alfaro-Jimenez-Jimenez-Morera.
*
*   Marzo 2019 
*/
#include <stdlib.h>
#include "context_list.h"
 
context_list *context_list_create()
{
    context_list *list = malloc(sizeof(context_list));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
        list->count = 0;
    }
 
    return list;
}
 
void context_list_empty(context_list *list)
{
    node *n, *temp;
    n = list->head;
    while (n != NULL) {
        temp = n->next;
        free(n);
        n = temp;
    }
}

void context_list_add_tail(context_list *list, node *data)
{
    node *n = data;
    if (list->head == NULL) {
        /* Adding the first node */
        list->head = n;
        list->tail = n;
    }
    else {
        list->tail->next = n;
        list->tail = n;
    }
    list->count++;
}
 
void context_list_add_head(context_list *list, node *data)
{
    node *n = data;
    if (list->tail == NULL) {
        /* Adding the first node */
        list->head = n;
        list->tail = n;
    }
    else {
        n->next = list->head;
        list->head = n;
    }
    list->count++;
}

unsigned int context_list_get_count(const context_list *list)
{
    return list->count;
}
