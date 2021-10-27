#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int g;

int main() {
    int pid;
    
    printf("before forking the value of g = %d\n", g);
    printf("\n");
    if((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("child: pid = %d\n", getpid());
        printf("child: my parent pid = %d\n", getppid());
        g = 100;
        printf("child: after the modification of g = %d\n", g);
        printf("child: I'm about to exit\n");
        printf("\n");
        exit(41);
    } else if (pid > 0) {
        int status;
        wait(&status);
        printf("parent: pid = %d\n", getpid());
        printf("parent: exit status of child = %d\n", WEXITSTATUS(status));
        printf("parent: after child midifying g = %d\n", g);
        printf("\n");
    }
    
    printf("common statement to parent and child processes\n");
    printf("\n");
    
    exit(0);
    
}
