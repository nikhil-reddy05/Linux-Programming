#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

int a(char* s, jmp_buf context) {
    int i = setjmp(context);
    
    printf("setjmp() returned -- %d\n", i);
    printf("s = %s\n", s);
    
    return i;
}

int b(int i, jmp_buf context) {
    printf("In b: i = %d, calling longjmp()\n", i);
    longjmp(context, i);
}

int main(void) {
    jmp_buf context;
    
    if (a("Bob", context) != 0)
        exit(0);
    
    b(3, context);
    
    return 0;
}
