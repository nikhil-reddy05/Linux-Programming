#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    
    FILE * fp;
    char ch;

    fp = fopen(argv[1], "r");
    
    if(fp == NULL) {
        perror("fopen");
        printf("usage: mycat <filename>\n");
        exit(1);
    }
    
    while( (ch=fgetc(fp)) != EOF)
        putchar(ch);
    
    fclose(fp);
    exit(0);
}

