#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char* argv[]) {
    int fd;
    char buf[81];
    
    fd = open (argv[1], O_WRONLY);
    
    lseek(fd, 50, SEEK_SET);
    write(fd, "ending", 6);
    printf("\nCurrent cursor position %lld\n", lseek(fd, 0, SEEK_CUR));
    
    close(fd);
    
    exit(0);
    
}

