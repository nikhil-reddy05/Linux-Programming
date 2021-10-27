#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int pid;
    pid = fork();
    
    if (pid <0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        int status;
        sscanf(argv[1], "%d", &status);
        exit(status);
    }
    else if (pid > 0) {
        int status;
        wait(&status);
        int number = WEXITSTATUS(status);
        for (int i=0; i<20; i++)
            printf("%d ", number++);
    }
    exit(0);
}
