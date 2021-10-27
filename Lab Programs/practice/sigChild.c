#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int status;
void childHandler(int signal){
    wait(&status);
}

int main(void){

    signal(SIGCHLD, childHandler);

    int pid;

    if((pid = fork()) < 0){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        exit(24);
    } else if(pid > 0){
        pause();
        if(WIFEXITED(status)){
            printf("parent: child's exit status = %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}