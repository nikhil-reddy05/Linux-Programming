 /*

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int buf = 0;

// sem_t readData;
// sem_t wroteData;

sem_t *s1;
sem_t *s2;
static const char *semname1 = "Semaphore1";
static const char *semname2 = "Semaphore2";

pthread_mutex_t wm = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rm = PTHREAD_MUTEX_INITIALIZER;

void* writer(void *arg){

    for(int i = 0; i <= 20; i++){
        pthread_mutex_lock(&wm);
        sem_post(s1);
        printf("writer thread wrote : %d\n", buf = i);
        sem_wait(s2);
        pthread_mutex_unlock(&wm);
        usleep(1000000);
    }
    pthread_exit(NULL);
}

void* reader(void *arg){
    
    for(int i = 0; i <= 20; i++){
        pthread_mutex_lock(&rm);
        sem_wait(s1);
        printf("reader read  buffer : %d \n\n", buf);
        sem_post(s2);
        pthread_mutex_unlock(&rm);
        //usleep(1000000);
    }
    pthread_exit(NULL);
}

int main(void){
  pthread_t r,w;

   s1 = sem_open(semname1, O_CREAT, 0777, 0);
   s2 = sem_open(semname2, O_CREAT, 0777, 0);
   
  pthread_create(&w, NULL , writer , NULL);
  pthread_create( &r ,NULL , reader, NULL);

  pthread_join(w , NULL);
  pthread_join(r, NULL);
  return 0;
  
 }

 */


// /*
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int buf = 0;

sem_t readData;
sem_t wroteData;

pthread_mutex_t wm = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rm = PTHREAD_MUTEX_INITIALIZER;

void* writer(void *arg){

    for(int i = 0; i <= 20; i++){
        pthread_mutex_lock(&wm);
        sem_wait(&readData);
        printf("writer thread wrote : %d\n", buf = i);
        sem_post(&wroteData);
        pthread_mutex_unlock(&wm);
        // usleep(1000000);
    }
    pthread_exit(NULL);
}

void* reader(void *arg){
    for(int i = 0; i <= 20; i++){
        pthread_mutex_lock(&rm);
        sem_wait(&wroteData);
        printf("reader read  buffer : %d\n\n", buf);
        sem_post(&readData);
        pthread_mutex_unlock(&rm);
    }
    pthread_exit(NULL);
}

int main(void){

  pthread_t r,w;

  sem_init(&wroteData, 0, 0);
  sem_init(&readData, 0, 1);
  
  pthread_create(&w, NULL , writer , NULL);
  pthread_create( &r ,NULL , reader, NULL);

  pthread_join(w , NULL);
  pthread_join(r, NULL);

  return 0;
  
 }

// */