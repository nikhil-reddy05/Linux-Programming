#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define REND 0
#define WEND 1

int main(int argc, char* argv[]) {
    
    int fd[2];
    int pid;
    pipe(fd); // creates unnamed pipes and kernel fills fd[0] and fd[1] unnamed pipes
    pid = fork(); // create child process
    
    if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0) { // child process
        
        close(fd[REND]); // making child as dedicated write process
        dup2(fd[WEND], STDOUT_FILENO); // redirect childs output to write end of the pipe
        execlp(argv[1], argv[1], (char*)0);
        exit(EXIT_SUCCESS);
        
    } else if (pid > 0) { // parent process
        char buf[13];
        int status;
        
        wait(&status); // blocks the parent untill child exits
        close(fd[WEND]); // making parent as dedicated read process
        dup2(fd[REND], STDIN_FILENO); // redirects the parents intput as read end of the pipe
        execlp(argv[2], argv[2], (char*)0);
        exit(EXIT_SUCCESS);
    }
}


