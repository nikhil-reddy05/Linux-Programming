#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#define BSIZE 10

int buf[BSIZE];
int count; 
int rear;
int front;

pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notempty = PTHREAD_COND_INITIALIZER;
pthread_cond_t notfull = PTHREAD_COND_INITIALIZER;


void * producer(void * args){
    int item;
    
    for(item = 1;item <= 20;item++){
        pthread_mutex_lock(&mutex);
        while(count>=BSIZE)
            pthread_cond_wait(& notfull,& mutex);
        buf[rear++]=item;
        printf("Produced:%d\n",item);
        rear=rear%BSIZE;
        count++;
        if(count > 0)
            pthread_cond_signal(& notempty);
        pthread_mutex_unlock(& mutex);
        usleep(100000);
    }
    pthread_exit(0);
}

void * consumer(void *ptr){
    int item;
    for(item=1;item<=20;item++){
        pthread_mutex_lock(&mutex);
        while(count<=0)
            pthread_cond_wait(&notempty,&mutex);
        item = buf[front++];
        front = front % BSIZE;
        count--;
        if(count == BSIZE-1)
            pthread_cond_signal(& notfull);
        pthread_mutex_unlock(&mutex);
        printf("consumed:%d\n", item);
    }
    pthread_exit(0);
}

int main(void){
    pthread_t p,c;
    count=0;
    front =0;
    rear=0;
    pthread_create(&p,NULL,producer,NULL);
    pthread_create(&c,NULL,consumer,NULL);
    pthread_join(p,NULL);
    pthread_join(c,NULL);
    return 0;
}

