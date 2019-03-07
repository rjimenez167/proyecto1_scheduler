/*
*   ITCR -- SOA -- Proyecto 1.
*   Loteria de threads.
*   Acuna-Alfaro-Jimenez-Jimenez-Morera.
*
*   Marzo 2019 
*/

#include "lotteryManager.h"
#include <stdlib.h>
#include <stdbool.h>

unsigned int getTotalAvailableTickets(node* head){
    unsigned int count = 0;
    node* n = head;
    while (n != NULL) {
        if(!n->completed){
            count += n->ticket_count;
        }
        n = n->next;
    }
    return count;
}


node* getWinnerTicket(node* head){
    node* n = head;
    unsigned int count = 0;
    unsigned int availableTickets = getTotalAvailableTickets(head);
    
    if(availableTickets > 0){
        int winnerTicket = rand() % availableTickets;
        printf("Winner %d\n", winnerTicket);
        // loop throught the list count the tickets and find the winner >= count
        while (n != NULL) {
            if(!n->completed){
                count += n->ticket_count;
                if(count >= winnerTicket){
                    return n;
                }
            }
            n = n->next;
        }
    }
    
    
    return NULL;
}

void completeWork(node* node){
    printf("ThreadId: %d has completed its task.\n", node->thread_id);
    node->completed = true;
}