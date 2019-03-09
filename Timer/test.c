#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "timer.h"

void example(int sig){
    printf("This is fucntion for testing\n");
}


int main() {
    set_timer(example, (useconds_t)100000, (useconds_t)200000);

    while(1){
        printf( "Hello\n" );
        usleep(10000);
    }
}