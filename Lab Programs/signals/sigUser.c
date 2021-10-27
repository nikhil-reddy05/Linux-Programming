#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char msg[81];

void userHandler(int signalNumber) {
    if (signalNumber == SIGUSR1)
        strcpy(msg, "USR1 signal received.");
    else
        strcpy(msg, "USR2 signal received.");
}

int main(void) {
    signal(SIGUSR1, userHandler);
    signal(SIGUSR2, userHandler);
    
    printf("Waiting for signals...\n");
    
    while (1) {
        pause();
        printf("%s\n", msg);
    }
}
