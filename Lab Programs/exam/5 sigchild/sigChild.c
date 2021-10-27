#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int status;

void childHandler(int signl) {
    wait(&status);
}

int main(void) {
    int pid; // Process ID
    
    signal(SIGCHLD, childHandler);
    
    pid = fork(); // Create a child process
    
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
        
    } else if (pid == 0) { // Child Process
        printf("Child processID is: %d\n", getpid());
        exit(117);
    } else if (pid > 0) { // Parent Process
        printf("Parent processID is: %d\n", getpid());
        
        pause();
        
        if (WIFEXITED(status))
            printf("Exit status of the child is: %d\n", WEXITSTATUS(status));
    }
    
    return 0;
}
