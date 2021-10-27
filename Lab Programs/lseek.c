#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, char* argv[]) {
    int fd;
    char buf[81];
    
    fd = open (argv[1], O_RDONLY);
    read(fd, buf, 11);
    buf[11] = '\0';
    write(STDIN_FILENO, buf, 11);
    printf("\nCurrent cursor position %lld\n", lseek(fd, 0, SEEK_CUR));
    
    read(fd, buf, 12);
    buf[12] = '\0';
    write(STDIN_FILENO, buf, 12);
    printf("\nCurrent cursor position %lld\n", lseek(fd, 0, SEEK_CUR));
    
    close(fd);
    
    exit(0);
    
}
