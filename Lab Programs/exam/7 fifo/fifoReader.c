#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(int argc, char *argv[]){
    int fd;

    fd = open(argv[1], O_RDONLY);
    if(fd < 0){
        perror("open");
        exit(1);
    }
    char buf[81];
    int n;

    while((n = read(fd, buf, 80)) > 0){
        buf[n] = '\0';
        printf("reader read %s", buf);
    }
    
    close(fd);
    return 0;
}

