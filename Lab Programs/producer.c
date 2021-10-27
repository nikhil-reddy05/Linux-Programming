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
	int key, i;
	struct sembuf sb;
	int *pShm = NULL;
	key =ftok("/Users/nikhilreddy/Documents/coding/Linux/Lab Programs",'S');
	if((shmid = shmget(key,sizeof(int),IPC_CREAT | 0666 ))<0){
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	if((pShm = shmat(shmid,NULL,0))==NULL){/*attach shm segment to address space*/
		perror("shmat");
		exit(EXIT_FAILURE);
	}
	if((semid = semget(key,2,IPC_CREAT | 0666))<0){
		perror("semget");
		exit(EXIT_FAILURE);
	}
	/*to avoid deadlock*/
	semctl(semid,CONSUMED , SETVAL , 1);/*initial consumed sem value to be 1*/
	i = 1;
	while(i <= 10){
		/*wait until prev item is consumed by consumer*/
		sb.sem_num = CONSUMED;
		sb.sem_op = -1;
		sb.sem_flg = SEM_UNDO;
		semop(semid , &sb,1);/*wait*/
		*pShm=i;/*new item production*/
		printf("New item %d is produced\n",*pShm);
		/*inform the consumer abt new production*/
		sb.sem_num=PRODUCED;
		sb.sem_op = +1;
		sb.sem_flg =SEM_UNDO;
		semop(semid,&sb,1);/*signal*/
		i++;
		if(i == 11) break;
		sleep(2);
	}
	shmdt(pShm);
	shmctl(shmid , IPC_RMID , NULL);
	semctl(semid , 0 , IPC_RMID , NULL);
	semctl(semid , 1 ,IPC_RMID , NULL);

	return 0;
}
