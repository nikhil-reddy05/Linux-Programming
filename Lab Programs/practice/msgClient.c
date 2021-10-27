#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<stdbool.h>

struct MsgType{
    long mtype;
    char command[50];
    char param[50];
    char result[10];
};

int main(void){
    struct MsgType msg,res;
    key_t key;
    int mqid, n, result;

    key = ftok("/", 'M');
    mqid = msgget(key, 0644);

    printf("commands accepted are\nisEven\nisPrine\nexit\n");

    while(1){
        printf("<command> ");
        scanf("%s", msg.command);
        if(!strncmp("exit", msg.command, 4)){
            msg.mtype = 1;
            msgsnd(mqid, &msg, sizeof(msg), 0);
            break;
        }
        printf("\n<param> ");
        scanf("%s", msg.param);

        msg.mtype = 1;
        msgsnd(mqid, &msg, sizeof(msg), 0);

        msgrcv(mqid, &res, sizeof(res), 2, 0);
        printf("%s %s %s\n", msg.command, msg.param, res.result);

    }

    msgctl(mqid, IPC_RMID, NULL);
    return 0;
}