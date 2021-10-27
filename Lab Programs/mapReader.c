#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<string.h>

int main(){
	int fd ,i;
	int *pMap = NULL;
	fd = open("./nums.bin", O_RDWR);
	if(fd < 0){
		perror("open");
		exit(1);
	}
	
	pMap=(int*)mmap(NULL,6*sizeof(int),PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if(pMap == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
	for(i = 0; i < 5; i++)
		printf("Reader read:%d\n", pMap[i]);
	munmap(pMap, 6*sizeof(int));
	close(fd);
}
