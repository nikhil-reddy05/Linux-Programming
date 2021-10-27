#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    int src, dest;

    if(argc != 3){
        printf("usage: %s <src> <dest>\n", argv[0]);
        exit(1);
    }

    src = open(argv[1], O_RDONLY);
    dest = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC | O_EXCL);

    char buffer[81];
    int n;

    while((n = read(src, buffer, 80)) > 0){
        write(dest, buffer, n);
    }

    close(src);
    close(dest);

    return 0;
}