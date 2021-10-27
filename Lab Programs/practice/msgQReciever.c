#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

struct msgType{
    long mtype;
    char mtext[200];
};

int main(void){

    struct msgType rcv;
    key_t key;
    int mqid, n;
    char buffer[81];

    key = ftok("/", 'M');
    mqid = msgget(key, 0644);
    while(1){
        msgrcv(mqid, &rcv, sizeof(rcv), 1, 0);
        printf("%s\n", rcv.mtext);
        if(!strncmp("exit", rcv.mtext, 4)){
            break;
        }
    }

    exit(0);
}