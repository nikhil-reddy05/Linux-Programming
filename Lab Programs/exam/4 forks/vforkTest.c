#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


int g;
int main() {
    int pid;
    
    printf("before forking the value of g = %d\n", g);
    printf("\n");
    if((pid = vfork()) < 0) { // clone parent process with common address space
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        g = 100;
        printf("child: after the modification of g = %d\n", g);
        printf("child: I'm about to exit\n");
        printf("\n");
        exit(41);
    } else if (pid > 0) {
//        int status;
//        wait(&status);
        printf("parent: after child midifying g = %d\n", g);
        printf("\n");
    }
    
    printf("common statement to parent and child processes\n");
    printf("\n");
    
    exit(0);
    
}
