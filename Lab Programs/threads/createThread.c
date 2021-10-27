#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* run(void* arg){

    for(int i = 0; i < 10; i++)
        printf("%d ", i);
    printf("\n");

    pthread_exit(NULL); // it exits only thread
}

int main(){
    pthread_t tid;

    pthread_create(&tid, NULL, run, NULL);  // id .... function params
    // creats a user level thread and runs
    pthread_join(tid, NULL); // main therad waits untill the user thread joins

    return 0;
}


// compilation and run --> gcc createThread.c -pthread -o createThread && ./createThread