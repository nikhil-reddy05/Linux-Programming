#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

sem_t readData;
sem_t wroteData;

pthread_mutex_t wm = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rm = PTHREAD_MUTEX_INITIALIZER;

int buffer;

void* writer(void* arg){
    for(int i = 1; i <= 20; i++){
        pthread_mutex_lock(&wm);
        sem_wait(&readData);
        printf("wrote: %d\n", buffer = i);
        sem_post(&wroteData);
        pthread_mutex_unlock(&rm);
    }
    pthread_exit(0);
}

void* reader(void* arg){
    for(int i = 1; i <= 20; i++){
        pthread_mutex_lock(&rm);
        sem_wait(&wroteData);
        printf("read: %d\n\n", buffer);
        sem_post(&readData);
        pthread_mutex_unlock(&rm);
    }
}




int main(void){
    pthread_t w, r;

    sem_init(&readData, 0, 1);
    sem_init(&wroteData, 0, 0);

    pthread_create(&w, NULL, writer, NULL);
    pthread_create(&r, NULL, reader, NULL);

    pthrea_join(w, NULL);
    pthread_join(r, NULL);

    return 0;

}


