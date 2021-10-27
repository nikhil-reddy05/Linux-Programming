#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void abortHandler(int signalNumber) {
    printf("Don't abort\n");
    return;
}

int main(void) {
    signal(SIGABRT, abortHandler);
    sleep(3);

    raise(SIGABRT); // Self signal
    
    return 0;
}
