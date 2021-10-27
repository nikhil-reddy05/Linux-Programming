#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int g;

int main(void){

    int pid;

    printf("before forking: value of g = %d\n", g);

    if((pid = vfork()) < 0){
        perror("vfork");
        exit(1);
    }

    if(pid == 0){
        g = 24;
        printf("child: modifying the value of g = %d\n", g);
        exit(0);
    } else if(pid > 0){
        int status;
        wait(&status);
        printf("parent: exit statu of child = %d\n", WEXITSTATUS(status));
        printf("parent: after child modifying the value of g = %d\n", g);
    }
    
    return 0;
}