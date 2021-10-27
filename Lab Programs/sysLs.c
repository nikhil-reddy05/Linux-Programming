#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int sys(const char* cmd) {
    int pid  = fork(); //clone parent process
    if (pid < 0) { // fork failure handling
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) { // child process
        // loading a program with cmd as name
        execl ("/bin/bash", "bash", "-c", cmd, (char*)NULL); // (char*)0
    } else if (pid > 0) { // parent
        int status;
        wait(&status); //waitpid(pid, &status, 0);
        if (WIFEXITED(status)) // nothing
            return WEXITSTATUS(status); //WEXISTSTATUS(status)
    }
    return -1;
}

int main(int argc, char* argv[]) {
    sys("clear");
    sys("ls -l");
    printf("hello world");
    exit(0);
}


/*
 
 int main(void) {
    char cmd[81];
    do {
        printf("#"); // prompting
        gets(cmd); // accepts user command
        sys(cmd);
    } while (0 != strcmp(cmd,"quit"));
    exit(0);
 }
 
 */
