#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fdSrc, fdDest, n;
    char buffer[80];
    
    fdSrc = open(argv[1], O_RDONLY);
    fdDest = open(argv[2],O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if( argc != 3 || fdSrc < 0 || fdDest < 0 ){
        perror("open");
        printf("usage: ./scp <srcFile> <destFile>");
        exit(1);
    }

    while ( (n = read(fdSrc, buffer, 80)) > 0) {
        write(fdDest, buffer, n);
    }
    
    close(fdSrc);
    close(fdDest);
    
    exit(0);
}
