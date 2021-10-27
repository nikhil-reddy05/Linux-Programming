#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *fp;
    char ch;
    int words=1,characters=0,lines=1;

    fp=fopen(argv[1],"r");

    if(fp==NULL){
        perror("fopen");
        printf("usage: ./desc <filename>\n");
        exit(1);
    }
    else{
      ch=fgetc(fp);
      while(ch!=EOF){
        if(ch==' '|| ch=='\n'){
            words++;
            if(ch=='\n')
            lines++;
        }
        else
            characters++;
        ch=fgetc(fp);
      }
    }
    printf("characters count : %d",characters);
    printf("word count : %d",words);
    printf("line count: %d",lines);
    
    exit(0);
}
