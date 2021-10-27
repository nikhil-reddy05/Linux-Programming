#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[]) {
    
    char ch;
    FILE* fds = NULL;
    FILE* fdd = NULL;
    
    
    char filename[50] = "upperOf";
    strcat(filename, argv[1]);
    fds = fopen(argv[1], "r");
    fdd = fopen(filename, "w");
    if (fds == NULL) {
        perror("open");
        printf("usage: ./up <filename>");
    }
    
    while ( (ch = fgetc(fds)) != EOF)
        fputc(toupper(ch), fdd);
    
    fclose(fds);
    fclose(fdd);
    exit(0);
}
