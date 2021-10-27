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
    pipe(fd); // kernel fills fd[0] and fd[1] unnamed pipes
//    write(fd[1], "CVR", 3);
//    read(fd[0], buf, 3);
//    buf[3] = '\0';
//    printf("content %s", buf);
    
    pid = fork();
    if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0) { // child process
        
        printf("Child read end fd is %d\n", fd[REND]);
        printf("Child write end fd is %d\n", fd[WEND]);
        close(fd[REND]); // making child as dedicated write process
        write(fd[WEND], "Hello Parent", 12);
        exit(EXIT_SUCCESS);
        
    } else if (pid > 0) { // parent process
        char buf[13];
        int status;
        wait(&status);
        
        printf("Parent read end fd is %d\n", fd[REND]);
        printf("Parent write end fd is %d\n", fd[WEND]);
        close(fd[WEND]); // making parent as dedicated read process
        
        read(fd[REND], buf, 12);
        buf[12] = '\0';
        printf("parent recieved %s from child\n",buf);
        exit(EXIT_SUCCESS);
    }
    
    return 0;
}
