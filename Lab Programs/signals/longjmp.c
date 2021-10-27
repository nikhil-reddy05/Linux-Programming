#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

jmp_buf buf;
int x;
int *px; // default value = 0

void segvHandler(int signalNo) {
    px = &x; // Proper address is assigned to px
    longjmp(buf, 1); // Non local jump to saved context
}

int main(void) {
    int ret;
    signal(SIGSEGV, segvHandler);
    
    ret = setjmp(buf); // Store the context in the buffer
    
    if (ret == 0) {  // SIGSEV is generated because px is an invalid pointer
        printf("Enter a number: ");
        scanf(" %d", px);
    } else {
        printf("Re enter the number: ");
        scanf(" %d", px);
    }
    
    printf("x = %d\n", x);
    return 0;
}
