#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "thread_func.h"

#define NUM_THREADS 100



int main()
{
    void *status;
    int thr_id;


    // create each thread
    pthread_t threads[NUM_THREADS];

    for(int i=0; i < NUM_THREADS; i++){
        /*create threads*/
        thr_id = pthread_create(&threads[i], NULL, &func1, NULL);
        if(thr_id < 0){
            perror("failure create thread");
        }
        else {
            printf("thread %d is created\n", i);
        }
        sleep(1);
    }




    // wait for all of thread dead
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &status);
    }

    //after dead all of thread
    printf("all of threads are dead\n");
    //announceOff();

    return 0;
}
