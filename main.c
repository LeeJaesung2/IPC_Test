#include <stdio.h>
#include <pthread.h>
#include "thread_func.h"

#define NUM_THREADS 2



int main()
{
    void *status;
    int thr_id;


    // create each thread
    pthread_t threads[NUM_THREADS];

    //create flight thread
    thr_id = pthread_create(&threads[0], NULL, &func1, NULL);
    if(thr_id < 0){
        perror("failure create thread");
    }
    // create receiver thread
    thr_id = pthread_create(&threads[1], NULL, &func1, NULL);
    if(thr_id < 0){
        perror("failure create thread");
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
