#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#define REND 0
#define WEND 1

int  main(void) {
    
   int  fd[2];
   int  pid1, pid2;
   
   pipe(fd); /* create pipe */
   if ((pid1 = fork()) < 0 ){ /* parent creates first child*/
    perror("fork");
    exit(EXIT_FAILURE);
   }
   if ( pid1 == 0 ){ /* first child process */
    close(fd[REND]); /* first child is the writer so close readend*/
    write(fd[WEND], "listening to child 1" , 20);
    close(fd[WEND]);
    exit(45); // exit status if child 1
   }
   else if ( pid1 > 0 ){ /* parent process */
    if ((pid2 = fork())< 0 ){ /* parent creates another child */
     perror("fork");
     exit(EXIT_FAILURE);
    }
    if( pid2 == 0 ){ /* second child process */
     char buf[21];
     close(fd[WEND]);
     read(fd[REND] , buf , 20);
     buf[20] = '\0';
     printf("Child 2 read: %s\n" , buf );
     close(fd[REND]);
      exit(87); // exit status if child 2
    }
    else if ( pid2 > 0 ){ /* parent process */
     int status1, status2;
     waitpid( pid1 , &status1, 0 ); /* wait for the first child */
     waitpid(pid2 , &status2, 0 ); /* wait for the second child */
     printf("child 1 exit status : %d\n", WEXITSTATUS(status1));
     printf("child 2 exit status : %d\n", WEXITSTATUS(status2));
    }
   }
   return 0;
}
