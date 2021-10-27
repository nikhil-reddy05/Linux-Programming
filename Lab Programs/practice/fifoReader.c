#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char* argv[]){

    int fd = open(argv[1], O_RDONLY);

    char buffer[81];
    int n;

    while((n = read(fd, buffer, 80)) > 0){
        buffer[n] = '\0';
        write(STDOUT_FILENO, buffer, n);
    }

    return 0;
}