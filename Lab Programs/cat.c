#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
int main(int argc, char *argv[]) {
    
    char buffer[81];
    int n, fdSrc, fdDest;
    
    fdSrc = STDIN_FILENO;
    fdDest = STDIN_FILENO;
   
    if (argc >= 2){
        if (!(strcmp(argv[1], "-n")==0) && !(strcmp(argv[1], "-a")==0)) {
            fdSrc = open(argv[1], O_RDONLY);
            if (fdSrc < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        }
        else if(strcmp(argv[1], "-n")==0) {
            fdDest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC | O_EXCL , 0644);
            if (fdDest < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        }
        else if ((strcmp(argv[1], "-a")==0)) {
            fdDest = open(argv[2], O_WRONLY | O_APPEND);
            if (fdDest < 0) {
                perror("open");
                exit(EXIT_FAILURE);
            }
        }
        else {
            printf("usage: ./mycat\n");
            printf("       ./mycat <filename>\n");
            printf("       ./mycat -n <filename>\n");
            printf("       ./mycat -a <filename>\n");
            exit(EXIT_FAILURE);
        }
    }
    
    while ((n = read(fdSrc, buffer, 80)) > 0) {
        buffer[n] = '\0';
        write(fdDest, buffer, n);
    }
    
    exit(0);
}
