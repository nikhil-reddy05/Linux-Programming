#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>

int main(void){
    int pid;

    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        printf("child: process id %d\n", getpid());
        exit(24);

    } else if(pid > 0) {
        int status;
        wait(&status);

        printf("parent: process id %d\n", getpid());
        printf("parent: my child's exit status %d\n", WEXITSTATUS(status));
    }

    return 0;
}