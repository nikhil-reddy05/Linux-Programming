#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>

struct msgType{
    long mtype;
    char mtext[200];
};

int main(void){

    struct msgType msg;

    key_t key;
    int mqid, n;
    char buffer[81];

    key = ftok("/", 'M');
    mqid = msgget(key, 0644|IPC_CREAT);

    msg.mtype = 1;

    while(fgets(msg.mtext, sizeof(msg), stdin) != NULL){
        msgsnd(mqid, &msg, sizeof(msg), 0);
        if(!strncmp("exit", msg.mtext, 4)){
            break;
        }
    }

    msgctl(mqid, IPC_RMID, NULL);

    exit(0);

}
