#include<stdio.h>
#include<stdlib.h>
#include<signal.h>

int  main(void){
  int  x;
  
  signal (SIGSEGV, segvHandler); // register the handler for SIGSEGV
  getchar();
  raise( SIGSEGV );
  printf("x = %d\n", x);
  exit(0);
}
