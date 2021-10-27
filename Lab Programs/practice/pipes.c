#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define REND 0
#define WEND 1

int main(void){
    int fd[2], pid;

    pipe(fd);
    pid = fork();
    if(pid < 0){
        perror("fork");
        exit(1);
    }

    if(pid == 0){
        close(fd[REND]);
        dup2(fd[WEND], STDOUT_FILENO);
        execlp("ls", "ls", "-l", NULL);
        exit(0);
    } else if (pid > 0){
        close(fd[WEND]);
        dup2(fd[REND], STDIN_FILENO);
        execlp("wc", "wc", NULL);
    }

    return 0;

}