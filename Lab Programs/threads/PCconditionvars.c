#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t pLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consumed = PTHREAD_COND_INITIALIZER;
pthread_cond_t produced = PTHREAD_COND_INITIALIZER;

int buffer = 0;

void* producer(void *ptr){
    int i;
    for(i = 0; i <= 20; i++){
        pthread_mutex_lock(&pLock);
        if(buffer != 0)
            pthread_cond_wait(&consumed, &pLock);
        printf("produced : %d\n", buffer = i);
        pthread_cond_signal(&produced);
        pthread_mutex_unlock(&pLock);
        usleep(90000);
    }
    pthread_exit(0);
}

void* consumer(void *ptr){
    int i;
    for(i = 0; i <= 20; i++){
        pthread_mutex_lock(&cLock);
        if(buffer == 0)
            pthread_cond_wait(&produced, &cLock);
        printf("consumed : %d\n", buffer);
        buffer = 0;
        usleep(100);
        pthread_cond_signal(&consumed);
        pthread_mutex_unlock(&cLock);
        
    }
    pthread_exit(0);
}

int main(){
    pthread_t pro, con;

    pthread_create(&con, NULL, consumer, NULL);
    pthread_create(&pro, NULL, producer, NULL);

    pthread_join(con, NULL);
    pthread_join(pro, NULL);

    printf("\n\n");
    return 0;

}