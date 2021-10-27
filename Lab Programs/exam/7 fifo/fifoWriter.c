#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){

    int fd;
    //printf("%s \n", argv[1]);
    mkfifo(argv[1], 0666);

    fd = open(argv[1], O_WRONLY);
    if(fd < 0){
        perror("open");
        exit(1);
    }
    
    char buf[81];
    int n;
    while((n = read(STDIN_FILENO, buf, 80)) > 0){
        buf[n] = '\0';
        write(fd, buf, n);
    }
    
    close(fd);
    return 0;
}

