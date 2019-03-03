#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "threads_gui.h"

#define NUM_THREADS 6
int main( int   argc,char *argv[])
{   
    int num_of_threads = NUM_THREADS;
    setup_gui_threads(argc, argv, num_of_threads);


    double progress[NUM_THREADS]={0.1,0.2,0.3,0.4,0,0};
  
    while(progress[3] <1){
        
        if(progress[3] < 0.9){
            for(int i=0;i<NUM_THREADS;i++){
                progress[i]=progress[i]+0.0001;
            }
        }

        update_pbar_array(progress);   
    }
    

    
    return 0;
}