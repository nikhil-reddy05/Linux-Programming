#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include <sys/types.h>


int main(int argc, char* argv[]) {
    int fd;
    char buf[81];
    
    fd = open (argv[1], O_WRONLY);

    int offset = lseek(fd, -24, SEEK_END);
    
    if (offset == (off_t) -1) {
        perror("lseek");
        exit(1);
    }
    write(fd, "starting ", 9);
    printf("\nCurrent cursor position %lld\n", lseek(fd, 0, SEEK_CUR));
    
    close(fd);
    
    exit(0);
    
}


