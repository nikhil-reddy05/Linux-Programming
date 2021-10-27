#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t pLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cLock = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t produced = PTHREAD_COND_INITIALIZER;
pthread_cond_t consumed = PTHREAD_COND_INITIALIZER;

int buffer = 0;

void* producer(void* prt){

    for(int i = 1; i <= 5; i++){
        pthread_mutex_lock(&pLock);
        if(buffer != 0 )
            pthread_cond_wait(&consumed, &pLock);

        printf("produced: %d\n", buffer = i);

        pthread_cond_signal(&produced);
        pthread_mutex_unlock(&pLock);
        sleep(1);
    }
    pthread_exit(0);

}

void* consumer(void* ptr){

    for(int i = 1; i <= 5; i++){
        pthread_mutex_lock(&cLock);
        if(buffer == 0)
            pthread_cond_wait(&produced, &cLock);
        
        printf("consumed: %d\n\n", buffer);
        buffer = 0;
        pthread_cond_signal(&consumed);
        pthread_mutex_unlock(&cLock);
        
    }


    pthread_exit(0);
}



int main(void){
    pthread_t pro, con;

    pthread_create(&pro, NULL, producer, NULL);
    pthread_create(&con, NULL, consumer, NULL);

    pthread_join(pro, NULL);
    pthread_join(con, NULL);

    exit(0);
}