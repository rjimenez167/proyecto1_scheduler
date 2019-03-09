/*
*   ITCR -- SOA -- Proyecto 1.
*   Loteria de threads.
*   Acuna-Alfaro-Jimenez-Jimenez-Morera.
*
*   Marzo 2019 
*/

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int t_id;
    double t_progress;
    struct nodo *next;
} nodoL;

struct nodo *last, *first; 
typedef nodoL *list_threads;


void add_list_progress(list_threads *L, int n_id, double n_progress);
int start_animation(nodoL *L);
void build_pbar(GtkWidget *vbox, GtkWidget **pbar_vector, int bar_num);
void build_pbar_array(GtkWidget *vbox, GtkWidget **pbar_vector, int number_of_threads);
void setup_gui_threads(int argc, char *argv[], int number_of_threads);
void update_pbar_array(double progress, int t_id);
