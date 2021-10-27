#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    struct flock fl;
    int fd;
    char c;
    
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();
    
    fd = open(argv[1], O_RDWR);
    fcntl(fd, F_SETLKW, &fl);
    printf("Lock acquired.\n");
    printf("Press any key to release the lock.\n");
    
    getchar();
    
    fl.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &fl);
    printf("Lock released on the file %s\n", argv[1]);
    
    close(fd);
    exit(0);
}
