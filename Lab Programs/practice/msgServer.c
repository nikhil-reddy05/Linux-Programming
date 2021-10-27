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

int isEven(int n){
    return (n%2 == 0);
}

int isPrime(int n){
    for(int i = 2; i < n; i++)
        if(n%i == 0) return true;
    return false;
}

int main(void){
    struct MsgType msg,res;
    key_t key;
    int mqid, n, result;

    key = ftok("/", 'M');
    mqid = msgget(key, 0644|IPC_CREAT);

    msg.mtype = 1;
    while(1){

        msgrcv(mqid, &msg, sizeof(msg), 1, 0);
        if(!strncmp(msg.command, "exit", 4)){
            strcpy(res.command, msg.command);
            res.mtype = 2;
            msgsnd(mqid, &res, sizeof(res), 0);
            break;
        }
        printf("server recieved: %s %s\n", msg.command,msg.param);
        if(!strncmp("isEven", msg.command, 6)){
            result = isEven(atoi(msg.param));
        } else {
            result = isPrime(atoi(msg.param));
        }

        if(result){
            strcpy(res.result,"true");
        } else {
            strcpy(res.result, "false");
        }

        res.mtype = 2;
        msgsnd(mqid, &res, sizeof(res), 0);
        printf("answer sent to client : %s\n", res.result);
    }
}