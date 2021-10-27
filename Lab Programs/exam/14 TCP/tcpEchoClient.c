#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<strings.h>
#include<sys/wait.h>
#include <unistd.h>


int main(void){
	
	int clifd;
	socklen_t cliaddrlen;
	struct sockaddr_in servaddr;
	int optval, n;
	char buf[81];

	clifd = socket( AF_INET, SOCK_STREAM, 0); // step 1
	if(clifd < 0){
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
	if(connect(clifd, (struct sockaddr*)&servaddr, sizeof(servaddr) ) < 0) {
		perror("connect");
		exit(1);
	}

	while(1) {
		printf("enter message to the server : ");
		fgets(buf, 80, stdin);
		n = strlen(buf);
		buf[n] = '\0';
		
		send(clifd, buf, n, 0); // write(clifd, buf, n);
		buf[0] = '\0';
		n  = recv(clifd, buf, 80, 0);
		buf[n] = '\0';
		printf("client recieved : %s\n", buf);

		if (strncmp("exit", buf, 4) == 0)
			break;
	}

	close(clifd);
	printf("\ngood bye...\n");
	return 0;
}


//gcc tcpClient.c -o tcpClient && ./tcpClient