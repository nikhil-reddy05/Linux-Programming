#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define REND 0
#define WEND 1

int main(void) {
    
    int fd[2];
    int pid;
    pipe(fd);
    pid = fork();
    if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0) { 
        close(fd[REND]); 
        dup2(fd[WEND], STDOUT_FILENO);
        //printf("exec c");
        execlp("ls","ls", "-l", NULL);
        exit(EXIT_SUCCESS);
    } else if (pid > 0) { // parent process
        int status;
        wait(&status);
        
        close(fd[WEND]);
        dup2(fd[REND], STDIN_FILENO);
        //printf("exec p");
        execlp("wc","wc", NULL);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}

