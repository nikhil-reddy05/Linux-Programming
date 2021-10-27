#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<stdlib.h>

void * run (void * args ){
	int i;
	printf("within thread stack, &i = %p\n" ,&i);
	for( i = 0 ; i < 16538 ; i++);
	
	printf("Thread finished\n");
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;
	int policy;
	void * stack = NULL;
	pthread_attr_init(&attr);
	stack = malloc(32768);
	printf("created stack starts at %p\n" , stack);
	printf("stack starting address = %p\n" , stack);
	pthread_attr_setstack( &attr , stack , 32768);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_attr_setschedpolicy( &attr , SCHED_RR);
	pthread_attr_getschedpolicy( &attr , &policy);
	if(policy ==SCHED_RR )
		printf("Threads follow Round Robin\n");
	else if( policy == SCHED_FIFO )
		printf("Threads follow FIFO \n");
	else if( policy == SCHED_OTHER )
		printf("Threads follow OTHER \n");

	pthread_create (&tid , &attr , run , NULL );

	if(EINVAL== pthread_join( tid,NULL ) )
		perror("pthread_join");
	return 0;
}
	
	
	
	
	
	
	
