#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "threads_gui.h"

GtkWidget *window;
GtkWidget *vbox;
GtkWidget *pbar;
GtkWidget *button;
GtkWidget **pbar_vector;
int number_of_pbars;

void destroy_progress( GtkWidget    *widget,gpointer *pdata){
    gtk_main_quit ();
}

void build_pbar(GtkWidget *vbox, GtkWidget **pbar_vector, int bar_num){
    pbar_vector[bar_num] = gtk_progress_bar_new ();
    gtk_container_add (GTK_CONTAINER (vbox), pbar_vector[bar_num]);
    gtk_widget_show (pbar_vector[bar_num]);
}

void build_pbar_array(GtkWidget *vbox, GtkWidget **pbar_vector, int number_of_threads){
    for(int i=0; i<number_of_threads; i++){
        build_pbar(vbox, pbar_vector, i);
    }
}

void setup_gui_threads( int   argc,char *argv[], int number_of_threads){
    number_of_pbars=number_of_threads;
    gtk_init (&argc, &argv);
    pbar_vector = (GtkWidget **)malloc(sizeof(GtkWidget *)*number_of_pbars);

    window= gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable (GTK_WINDOW (window), TRUE);

    g_signal_connect (window, "destroy",G_CALLBACK (destroy_progress),NULL);
    gtk_window_set_title (GTK_WINDOW (window), "GtkProgressBar");
    gtk_container_set_border_width (GTK_CONTAINER (window), 0);


    vbox = gtk_vbox_new (FALSE, 5);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    build_pbar_array(vbox, pbar_vector, number_of_pbars);

        /* Add a button to exit the program */
    button = gtk_button_new_with_label ("close");
    g_signal_connect_swapped (button, "clicked",
                              G_CALLBACK (gtk_widget_destroy),
                            window);
    gtk_box_pack_start (GTK_BOX (vbox), button, FALSE, FALSE, 0);

    /* This makes it so the button is the default. */
    gtk_widget_set_can_default (button, TRUE);
        /* This grabs this button to be the default button. Simply hitting
     * the "Enter" key will cause this button to activate. */
    gtk_widget_grab_default (button);
    gtk_widget_show (button);
    
    gtk_widget_show (window);
}

void update_pbar_array(double *progress){
    for(int i=0; i<number_of_pbars; i++){
        gtk_progress_bar_update (GTK_PROGRESS_BAR ((GtkWidget *)pbar_vector[i]), (gdouble) progress[i]);
    }
    gtk_main_iteration_do(FALSE);
}
