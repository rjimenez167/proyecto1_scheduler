/*
*   ITCR -- SOA -- Proyecto 1.
*   Loteria de threads.
*   Acuna-Alfaro-Jimenez-Jimenez-Morera.
*
*   Marzo 2019 
*/

#ifndef LOTTERYMANAGER_H
#define LOTTERYMANAGER_H

#include "../threads/context_list.h"

unsigned int getTotalAvailableTickets(node*);
node* getWinnerTicket(node*);
void completeWork(node* node);
#endif