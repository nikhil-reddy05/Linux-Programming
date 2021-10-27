#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define PRODUCED 0
#define CONSUMED 1

int main(){
	int shmid ,semid;
	int key , i;
	struct sembuf sb;
	int *pShm = NULL;/*step 0*/
	key =ftok("/Users/nikhilreddy/Documents/coding/Linux/Lab Programs",'S');/*creat shm segmet*/
	if((shmid = shmget(key,sizeof(int),0666 ))<0){
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	if((pShm = shmat(shmid,NULL,0))==NULL){/*attach shm segmet to address space*/
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	if((semid = semget(key,2,0666))<0){
		perror("semget");
		exit(EXIT_FAILURE);
	}
	i=1;
	while( i <= 10){
		/*wait until new item is produced by producer*/
		sb.sem_num = PRODUCED;
		sb.sem_op = -1;
		sb.sem_flg = SEM_UNDO;
		semop(semid , &sb,1);/*wait*/
		printf("%d is consumed\n",*pShm);/*new item production*/
		/*inform the producer about consumption of item*/
		sb.sem_num=CONSUMED;
		sb.sem_op = +1;
		sb.sem_flg =SEM_UNDO;
		semop(semid,&sb,1);/*signal*/
		if(*pShm == 10) break;
	}
	shmdt(pShm);
	return 0;
}
