#include<pthread.h>
#include<stdlib.h>
#include<sys/time.h>

#include <stdio.h>

#ifndef CHUNKSIZE
#define CHUNKSIZE 1024
#endif
#define THREADS 4

struct ArgsType
{
	float *base;
	int length ;
};
typedef struct ArgsType Args;
float list[CHUNKSIZE *THREADS]; /* shared among all threads */
void * startRoutine (void * args )
{

	int i;
	Args * pa = (Args * )args;
	float  *psum = (float *)malloc (sizeof (float));
	*psum = 0;
	for( i = 0 ; i < pa ->length; i++ )
		*psum = *psum + pa->base[i];
	pthread_exit(psum);
}

int main(void){
	int i;
	pthread_t tid[THREADS];
	Args param[THREADS];
	float parallelsum = 0.0;
	float serialsum = 0.0;
	float ts, tp;
	struct timeval s, e;
	/*intialize the array */
	for( i = 0; i<CHUNKSIZE *THREADS; i++)
		list[i] = i*1.0;
	gettimeofday(&s,NULL);
	for( i = 0 ; i < CHUNKSIZE *THREADS ; i ++)
		serialsum = serialsum + list[i];
	gettimeofday(&e,NULL);
	ts = (e.tv_sec + e.tv_usec/1000000.0) - (s.tv_sec + s.tv_usec/1000000.0);
	printf("serial execution times=%f\n" , ts);
	gettimeofday(&s,NULL);
	for( i = 0 ; i <THREADS ; i ++ )
	{
		param[i].base = &list[ i*CHUNKSIZE];
		param[i].length = CHUNKSIZE;
		pthread_create( &tid[i] , NULL , startRoutine ,(void*)&param[i] );
	}
	for( i = 0 ; i < THREADS ; i++)
	{
		float *p;
		pthread_join ( *(tid+i) ,(void*)&p );
		parallelsum = parallelsum+ *p;
		
	}
	gettimeofday(&e,NULL);
	tp = (e.tv_sec + e.tv_usec/1000000.0) - (s.tv_sec +s.tv_usec/1000000.0);
	printf("paralle execution time = %f\n" ,tp);
	printf("parallelsum = %f\n",parallelsum );
	
	return 0;
	
}
