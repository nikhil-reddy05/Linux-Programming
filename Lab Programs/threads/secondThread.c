#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* run(void* arg){

    int* psum;
    psum = (int*) malloc(sizeof(int));

    for(int i = 1; i <= 20; i++)
        *psum += i;

    pthread_exit(psum); 
}

int main(){

    pthread_t tid;
    int* psum;
    pthread_create(&tid, NULL, run, NULL);
    pthread_join(tid, (void**)&psum);
    printf("sum = %d\n", *psum);
    return 0;
}


// compilation and run --> gcc secondThread.c -pthread -o secondThread && ./secondThread