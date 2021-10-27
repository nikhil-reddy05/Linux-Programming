#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<string.h>
struct msg_type{
    long  mtype;
    char mtext[200];
};
int main(void){
    struct msg_type msg;
    key_t key;
    int msgqid, len;

    key = ftok("/", 'M');
    msgqid = msgget(key, 0644|IPC_CREAT);
    printf("Enter messages to send : \n");
    msg.mtype = 1;
    while(fgets(msg.mtext, sizeof(msg.mtext), stdin) != NULL){
       if((msgsnd(msgqid, &msg, sizeof(msg), 0)) == -1){ // last parameter 0 means -> blocking message queue
            perror("msgsnd");
            exit(1);
       }
       if(!strncmp("end", msg.mtext, 3)){
           break;
       }
    }

    if((msgctl(msgqid, IPC_RMID, NULL)) == -1){
        perror("msgctl");
        exit(1);
    }

    printf("bye...\n");
    return 0;
}