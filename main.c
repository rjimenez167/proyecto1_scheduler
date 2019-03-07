/*
*   ITCR -- SOA -- Proyecto 1.
*   Loteria de threads.
*   Acuna-Alfaro-Jimenez-Jimenez-Morera.
*
*   Marzo 2019 
*/

//feature test macros. These allow us to use stuff that is not part
//of the standard C library. Must be defined before the include statements
//DEFAULT -- allows for using usleep(ms) method
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>
#include<time.h> 

#include "threads/context_list.h"
#include "lottery/lotteryManager.h"


//constant -> second (unit of time) definition in miliseconds
#define SLEEP 5000
//constant -> size of each thread's stack
#define STACK_SIZE 4096
//constant -> minimal work unit
#define MIN_WORK_UNIT 50

//current thread context
node *head, *current;
char op_mode; // it´s global because it's going to be used by other funtions

#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr){
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
                 "rol    $0x11,%0\n"
                 : "=g"(ret)
                 : "0"(addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr){
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
                 "rol    $0x9,%0\n"
                 : "=g"(ret)
                 : "0"(addr));
    return ret;
}
#endif

void switchThreads(){
    //save env
    sigsetjmp(current->env, 1);
    
    current = getWinnerTicket(head);
    if(current != NULL){
        siglongjmp(current->env, 1);
    }else{
        printf("we have finished all");
    }
}

void doWork(){
    printf("thread with id: %d -- running and working on %d units!\n", current->thread_id, current->work_units);

    int terms = current->work_units * MIN_WORK_UNIT;

    double pi = 0;
    int denom = 1;
    int sign = 1;

    for (int i = 1; i <= terms; i++){
        pi += sign * 4.0 / denom;
        denom += 2;
        sign *= -1;

        usleep(SLEEP);
    }
    
    printf("%d terms processed -- Pi = %.32f\n", terms, pi);
    //finish thread
    completeWork(current);
    if(getTotalAvailableTickets(head) > 0){
        printf("switching\n");
        switchThreads();
    }else{
        exit(EXIT_SUCCESS); // TODO REMOVE THIS WHEN THE GUI IS USED
    }
}

void setup(context_list *ctx_list){
    printf("Setup is started\n"); 
    //Read data from the source csv.
    FILE *file = fopen("threads_setup.csv", "r");
    char line[1024];
    while (fgets(line, 1024, file)){
        //char *stack = malloc(STACK_SIZE * sizeof(char));
        node *n_node;
        n_node = malloc(sizeof(node));

        int id = 0;
        char *tmp = strdup(line);
        char *field = NULL;
        char *name = NULL;

        // rows value id|count|work|quantum|units
        n_node->thread_id = atoi(strsep(&tmp, "|"));
        n_node->ticket_count = atoi(strsep(&tmp, "|"));
        n_node->work_amount = atoi(strsep(&tmp, "|"));
        n_node->quantum = atoi(strsep(&tmp, "|"));
        n_node->work_units = atoi(strsep(&tmp, "|"));
        n_node->completed = false;
        n_node->stack = malloc(STACK_SIZE * sizeof(char));

        address_t sp, pc;
        sp = (address_t)n_node->stack + STACK_SIZE - sizeof(address_t);
        pc = (address_t)doWork;

        sigsetjmp(n_node->env, 1);
        (n_node->env->__jmpbuf)[JB_SP] = translate_address(sp);
        (n_node->env->__jmpbuf)[JB_PC] = translate_address(pc);
        sigemptyset(&n_node->env->__saved_mask);

        context_list_add_tail(ctx_list, n_node);
    }
    fclose(file);
    printf("Setup is finished\n"); 
}

void noExpropiation(context_list*);
void expropiation(context_list*);

int main(int argc, char **argv){
    srand ( time(NULL) );
    char usage_msj[] = "Usage: ./lottery < e | n >\n %s";

    if (argc < 2){
        fprintf(stderr, usage_msj, "Parameter count!\n");
        return 0;
    }

    op_mode= *argv[1];

    if (!(op_mode == 101 || op_mode == 110)){ //E | N
        fprintf(stderr, usage_msj, "Wrong values!\n");
        return 0;
    }
    
    context_list *ctx_list = context_list_create();
    setup(ctx_list);
    
    switch (op_mode){
        case 'e':{
            expropiation(ctx_list);
            break;
        }
        case 'n':{
            noExpropiation(ctx_list);
            break;
        }
    }
    context_list_empty(ctx_list);
   
    return EXIT_SUCCESS;
}

void noExpropiation(context_list *ctx_list){
    head = ctx_list->head;
    current = ctx_list->head;

    printf("The total tickets is %d\n", getTotalAvailableTickets(head));
    current = getWinnerTicket(head);
    
    siglongjmp(current->env, 1);
}

void expropiation(context_list *ctx_list){
    
}