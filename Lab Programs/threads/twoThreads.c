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

    pthread_t tid1, tid2;
    int *psum1, *psum2;
    pthread_create(&tid1, NULL, run, NULL);  
    pthread_create(&tid2, NULL, run, NULL);

    pthread_join(tid1, (void**)&psum1);
    pthread_join(tid2, (void**)&psum2);

    printf("thread %d sum1 = %d\n", tid1, *psum1);
    printf("thread %d sum2 = %d\n", tid2, *psum2);

    return 0;
}


// compilation and run --> gcc twoThreads.c -pthread -o twoThreads && ./twoThreads