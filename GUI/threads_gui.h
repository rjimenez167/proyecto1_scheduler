#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

void destroy_progress( GtkWidget *widget,gpointer *pdata);

void build_pbar(GtkWidget *vbox, GtkWidget **pbar_vector, int bar_num);

void build_pbar_array(GtkWidget *vbox, GtkWidget **pbar_vector, int number_of_threads);

void setup_gui_threads( int   argc,char *argv[], int number_of_threads);

void update_pbar_array(double *progress);