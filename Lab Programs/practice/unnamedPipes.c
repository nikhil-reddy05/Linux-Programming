#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define REND 0
#define WEND 1

int main(void){

    int fd[2];
    pipe(fd);
    int pid;
    pid = fork();

    if(pid == 0){
        close(fd[REND]);
        write(fd[WEND], "hello", 5);
        exit(0);
    } else if(pid > 0){
        int s;
        wait(&s);
        close(fd[WEND]);
        char buffer[81];
        int n = read(fd[REND], buffer, 5);
        printf("%s\n", buffer);
    }
}