#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<unistd.h>
#define READDATA 0
#define WROTEDATA 1
int main(void){
    int key,shmId,semId;
    int *pShm;
    struct sembuf sb;

    if((key = ftok("/",'M')) <0){
        perror("ftok");
        exit(1);
    }
    if((shmId = shmget(key, sizeof(int),0666)) < 0){
        perror("shmget");
        exit(1);
    }
    if ((pShm = (int *)shmat(shmId , NULL ,0)) == NULL){
        perror("shmat");
        exit(1);
    }
    if((semId = semget(key,2,0666)) < 0){
        perror("semget");
        exit(1);
    }
    while ( *pShm <= 100){
        sb.sem_num = WROTEDATA;
        sb.sem_op = -1;
        sb.sem_flg = SEM_UNDO;
        semop(semId,&sb,1);
        printf("Reader read %d\n",*pShm);
        sb.sem_num = READDATA;
        sb.sem_op = +1;
        sb.sem_flg = SEM_UNDO;
        semop(semId,&sb,1);
    }
    shmdt(pShm);

    return 0;
}

