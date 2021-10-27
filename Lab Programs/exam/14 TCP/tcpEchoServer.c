#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/wait.h>
#include <unistd.h>


int main(void){
	
	int servfd, newSockfd;
	socklen_t cliaddrlen;
	struct sockaddr_in servaddr,cliaddr;
	//int optval;
	servfd = socket( AF_INET, SOCK_STREAM, 0); // step 1
	if(servfd < 0){
		perror("socket");
		exit(1);
	}
	// optval = 1;
	// setsocketopt( servfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(9090);

	// step 2
	if(bind(servfd, (struct sockaddr*)&servaddr, sizeof(servaddr) ) < 0) {
		perror("bind");
		exit(1);
	}

	listen(servfd, 5 ); //step 3
	
	// step 4
	newSockfd = accept(servfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
	if(newSockfd < 0){
		perror("accept");
		exit(1);
	}


	while(1){ // iterative server
		int n, pid;
		char buf[81];
		
		// client processing 
		n = recv(newSockfd, buf, 80, 0); // read(clifd, buf, 80);
		//printf("%s\n", buf);
		time_t t = time(NULL);
	  	strcpy(buf,ctime(&t));
		printf("server recieved : %s", buf);
		send(newSockfd, buf, n, 0);

		if ((strncmp("exit", buf, 4) == 0) || n == 0)
			break;

	}

	close(newSockfd);
	close(servfd);
	printf("\ngood bye...\n");
	return 0;
}


// gcc tcpServer.c -o tcpServer && ./tcpServer