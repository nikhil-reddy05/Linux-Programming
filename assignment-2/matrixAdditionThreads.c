/*matrix addition using threads */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define CORE 2
#define MAX 8

pthread_t threads[CORE];
int i, j, matA[MAX][MAX], matB[MAX][MAX], resMat[MAX][MAX];

void* addition(void* arg){

    int thread;
    thread = (int)arg;
    
    for(i = thread * MAX / CORE; i < (thread + 1) * MAX / CORE; i++)
        for(int j = 0; j < MAX; j++)
            resMat[i][j] = matA[i][j] + matB[i][j];

    pthread_exit(NULL);
}

int main(void){

    printf("Enter matrix A :\n");
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            scanf("%d", &matA[i][j]);
    
    printf("Enter matrix B :\n"); 
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            scanf("%d", &matB[i][j]);

    for (i = 0; i < CORE; i++)
        pthread_create(&threads[i], NULL, &addition, (void*)i);

    for (i = 0; i < CORE; i++) 
        pthread_join(threads[i], NULL); 
    

    printf("Resultant Matix\n");
    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++)
            printf("%d ", resMat[i][j]);
        printf("\n");
    }

    return 0;
    printf("\n\n");
}

