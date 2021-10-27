
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

struct MsgType {
    long type;
    char command[81];
    char param[21];
    char result[10];
};
typedef struct MsgType Msg;

int isPrime(int n){
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return 0;
    return 1;
}

int isEven(int n){
    if(n % 2 == 0)
        return 1;
    return 0;
}
int main(void) {
    int mqid;
    key_t key;
    int res;
    Msg m;
    key = ftok("/user/nikhilreddy/Documents/Coding/Linux Programing", 'M');
    if ((mqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    while(true) {
        
        printf("server is waiting for the command\n");
        msgrcv(mqid, &m, sizeof(m), 1, 0);
        //printf("%s",m.command );
        if(!(strcmp(m.command, "exit"))){
            break;
        }
        printf("recieved %s %s\n", m.command, m.param);
        
        if (!(strcmp(m.command, "isPrime"))) {
            res = isPrime(atoi(m.param));
        } else if (!(strcmp(m.command, "isEven"))) {
            res = isEven(atoi(m.param));
        }
        
        if (res){
            strcpy(m.result, "true");
        } else { 
            strcpy(m.result, "false");
        }
        m.type = 2;
        msgsnd(mqid, &m, sizeof(m), 0);
        printf("Answer sent to the client - %s\n", m.result);
        bzero(&m, sizeof(m));
    }
    
    printf("<command> exit\n");
    msgctl(mqid, IPC_RMID, 0);
    exit(0);
    
}

