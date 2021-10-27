#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>

int main(int agrc, char* argv[]){

    mkfifo(argv[1], 0666);

    int fd = open(argv[1], O_WRONLY);
    char buffer[81];
    int n;
    while((n = read(STDIN_FILENO, buffer, 80)) > 0 ){
        buffer[n] = '\0';
        write(fd, buffer, n);
    }
    return 0;
}
