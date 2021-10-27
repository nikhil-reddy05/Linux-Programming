#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *src = NULL;
    FILE *dst = NULL;
    int c;

    if(argc != 3){
        printf("usage: %s <src> <dst>\n",argv[0]);
        exit(1);
    }


    src = fopen(argv[1],"r");
    if(src == NULL){
        perror("fopen");
        exit(1);
    }

    dst = fopen(argv[2],"w");
    if(dst == NULL){
        perror("fopen");
        exit(1);
    }
    
    while((c=fgetc(src)) != EOF)
        fputc(c,dst);
    fclose(src);
    fclose(dst);
    exit(0);
}
