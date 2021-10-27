#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<string.h>
#include<sys/stat.h>
#include <unistd.h>

const char* toUpper (char* buffer) {
    for (int i=0; i<80; i++)
        buffer[i] = toupper(buffer[i]);
    return buffer;
}
int main(int argc, char *argv[]) {
    
    int fdSrc, fdDest, n;
    char buffer[80];

    char filename[50] = "upperOf";
    strcat(filename, argv[1]);
    
    fdSrc = open(argv[1], O_RDONLY);
    fdDest = open(filename,O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fdSrc < 0) {
        perror("open");
        printf("usage: ./up <filename>");
    }
    
    while ( (n = read(fdSrc, buffer, 80)) > 0) {
        write(fdDest, toUpper(buffer), n);
    }
    
    close(fdSrc);
    close(fdDest);
    
    exit(0);
}
