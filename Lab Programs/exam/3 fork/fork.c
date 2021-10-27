#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// int main() {
//     int pid;
//     if((pid = fork()) < 0) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     } else if (pid == 0) {
//         printf("child: pid = %d\n", getpid());
//         printf("child: I'm about to exit\n");
//         printf("\n");
//         exit(41);
//     } else if (pid > 0) {
//         int status;
//         wait(&status);
//         printf("parent: pid = %d\n", getpid());
//         printf("parent: exit status of child = %d\n", WEXITSTATUS(status));
    
//     }    
//     exit(0);
    
// }


int main() {
    int pid,p;
    pid = fork();
    if(pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        
        printf("child: pid = %d\n", getpid());
        printf("child: I'm about to exit\n");
        printf("\n");
        exit(41);
    } else if (pid > 0) {
        int status;
        wait(&status);
        printf("parent: pid = %d\n", getpid());
        printf("parent: exit status of child = %d\n", WEXITSTATUS(status));
    
    }    
    exit(0);
    
}
