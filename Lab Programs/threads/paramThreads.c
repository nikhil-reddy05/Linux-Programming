#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* run(void* arg){

    int *psum;
    int start;
    start = *(int *)arg;
    psum = (int*) malloc(sizeof(int));

    for(int i = start; i <= 40; i += 2)
        *psum += i;

    pthread_exit(psum); 
}

int main(){

    pthread_t tid1, tid2;
    int *psum1, *psum2;
    int start1= 1, start2 = 2;
    pthread_create(&tid1, NULL, run, (void*)&start1);  
    pthread_create(&tid2, NULL, run, (void*)&start2);

    pthread_join(tid1, (void**)&psum1);
    pthread_join(tid2, (void**)&psum2);

    printf("total sum = %d\n", *psum1 + *psum2);
    printf("thread %d odd sum = %d\n", (int)tid1, *psum1);
    printf("thread %d even sum = %d\n", (int)tid2, *psum2);

    return 0;
}


// compilation and run --> gcc paramThreads.c -pthread -o paramThreads && ./paramThreads