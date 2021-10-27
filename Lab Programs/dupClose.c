#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int agrc,char * argv[]) {
    
    int oldFd, newFd;
    
    oldFd = open(argv[1], O_RDONLY);
    if(oldFd < 0){
      perror("open");
      exit(EXIT_FAILURE);
    }
    
    printf("The old file descriptor value is: %d\n",oldFd);
    close(STDIN_FILENO);
    newFd=dup(oldFd);
    printf("The new file descriptor value is: %d\n",newFd);
    
    close(newFd);
    
    exit(0);
}


