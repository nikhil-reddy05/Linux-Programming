#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

struct MsgType {
    long type;
    char command[81];
    char param[21];
    char res[10];
};

typedef struct MsgType Msg;

int main () {
    int mqid;
    key_t key;
    int res;
    Msg m, r;
    key = ftok("/user/nikhilreddy/Documents/Coding/Linux Programing", 'M');
    if ((mqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    while(true) {
        
        printf("\nCommands supported\nisEven\nisPrime\nExit\n");
        printf("<command> ");
        scanf("%s", m.command);
        
        if (strcmp(m.command, "exit") != 0) {
            printf("<param> ");
            scanf("%s", m.param);
            m.type = 1;
            msgsnd(mqid, &m, sizeof(m), 0);
            
            msgrcv(mqid, &r, sizeof(r), 2, 0);
            printf("Answer from the sever : %s\n", r.res);
        } else{
            m.type = 1;
            msgsnd(mqid, &m, sizeof(m), 0);
            break;
        }
    }
    
    msgctl(mqid, IPC_RMID, 0);
    exit(0);
    
}


