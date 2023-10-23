#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "Producer-consumer.hpp"

#define NUM_THREADS 2
#define BUFFER_SIZE 26

using namespace std;


struct MsgBuf {
    long msgtype; // message type, must be > 0
    int value;
    char buf[BUFFER_SIZE];
};

int mq_init(key_t key){

    int key_id = msgget( key, IPC_CREAT|0666);
    if (key_id == -1) {
        cerr << "Message Get Failed!" << endl;
        exit(EXIT_FAILURE);
    }
    return key_id;
}

int mian(void){

    //create ipc1
    int queue1 = mq_init((key_t)1234);
    //create ipc2
    int queue2 = mq_init((key_t)2345);

    pid_t pid = fork();

    //process2
    if(pid==0){
        printf("child process");
        int thr_id;
        void *status;
        pthread_t threads[NUM_THREADS];

        //create producer thread
        thr_id = pthread_create(&threads[0],NULL,&producer,&queue2); //send ipc2 id as arg
        if(thr_id <0 ){
            perror("failure creste thread");
        }

        //create consumer thread
        thr_id = pthread_create(&threads[1],NULL,&consumer,&queue1); //send ipc1 id as arg
        if(thr_id <0 ){
            perror("failure creste thread");
        }
        for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &status);
    }

    }

    //process2   
    else{
        printf("parent process");
        printf("child process");
        int thr_id;
        void *status;
        pthread_t threads[NUM_THREADS];

        //create producer thread
        thr_id = pthread_create(&threads[0],NULL,&producer,&queue1); //send ipc1 id as arg
        if(thr_id <0 ){
            perror("failure creste thread");
        }

        //create consumer thread
        thr_id = pthread_create(&threads[1],NULL,&consumer,&queue2); //send ipc2 id as arg
        if(thr_id <0 ){
            perror("failure creste thread");
        }
        for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &status);
    }

    } 

    

    printf("all of threads are dead");

    return 0;

}


