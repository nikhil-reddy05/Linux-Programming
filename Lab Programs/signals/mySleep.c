#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarmHandler(int signalNumber) {
    return;
}

unsigned mySleep(unsigned int nSecs) {
    signal(SIGALRM, alarmHandler);
    alarm(nSecs);
    pause();
    return alarm(0);
}

int main() {
    printf("Entering into sleep for 5 seconds...\n");
    mySleep(5);
    printf("Woke up after sleep...\n");
}
