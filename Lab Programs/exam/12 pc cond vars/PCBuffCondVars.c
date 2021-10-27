#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t plock=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t clk=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t consumed = PTHREAD_COND_INITIALIZER;
pthread_cond_t produced = PTHREAD_COND_INITIALIZER;
int buffer = 0;

void * producer(void * ptr){
    int i;
    for(i = 1;i <= 40;i++){
        pthread_mutex_lock(&plock); 
        if(buffer != 0)
            pthread_cond_wait(&consumed, &plock);
        printf("Produced:%d\n",buffer =i);
        
        pthread_cond_signal(& produced);
        pthread_mutex_unlock(& plock);
        usleep(90000);
    }
    pthread_exit(0);
}

void * consumer(void *ptr){
    int i;
    for(i=1;i<=40;i++){
        pthread_mutex_lock(&clk);
        if(buffer == 0)
            pthread_cond_wait(&produced,&clk);
        printf("consumed:%d\n\n", buffer);
        buffer=0;
        usleep(100);
        pthread_cond_signal(&consumed);
        pthread_mutex_unlock(&clk);
        
    }
    pthread_exit(0);
}

int main(void){

    pthread_t pro,con;
    //create the threads
    pthread_create(&con,NULL,consumer,NULL);
    pthread_create(&pro,NULL,producer,NULL);
    //wait for the threads to finish
    pthread_join(con,NULL);
    pthread_join(pro,NULL);

    return 0;
}

