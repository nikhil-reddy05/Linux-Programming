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

    struct msg_type recv;
    key_t key;
    int msgqid, len;

    key = ftok("/", 'M');
    msgqid = msgget(key, 0644);
    char buf[81];
    printf("Recieved messages : \n");
    while(1){
       if((msgrcv(msgqid, &recv, sizeof(recv), 1, 0)) == -1){
            perror("msgrcv");
            exit(1);
       }
       printf("%s\n",recv.mtext);
       if(!strncmp("end", recv.mtext, 3)){
           break;
       }
    }
    printf("bye...\n");
    return 0;
}