#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

void set_timer(void(*callback_pointer)(int), useconds_t time_for_first_signal, useconds_t interval);