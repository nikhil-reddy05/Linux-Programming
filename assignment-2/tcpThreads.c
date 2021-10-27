/* tcp echo server and client using threads */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<strings.h>
#include<sys/wait.h>
#include <unistd.h>



void *tcpServer(void *arg){

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
}

void *tcpClient(void *arg){

    int servfd, clifd;
	socklen_t cliaddrlen;
	struct sockaddr_in servaddr,cliaddr;
	int optval;
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
	clifd = accept(servfd, (struct sockaddr*)&cliaddr, &cliaddrlen);
	if(clifd < 0){
		perror("accept");
		exit(1);
	}


	while(1){ // iterative server
		int n, pid;
		char buf[81];
		
		// client processing 
		n = recv(clifd, buf, 80, 0); // read(clifd, buf, 80);
		//printf("%s\n", buf);
		buf[n] = '\0';
		printf("server recieved : %s", buf);
		send(clifd, buf, n, 0);

		if ((strncmp("exit", buf, 4) == 0) || n == 0)
			break;

	}

	close(clifd);
	close(servfd);
	printf("\ngood bye...\n");

}

int main(void){
    pthread_t server, client;

    pthread_create(&server, NULL, &tcpServer, NULL);
    pthread_create(&client, NULL, &tcpClient, NULL);

    pthread_join(server, NULL);
    pthread_join(client, NULL);

    printf("\n\n");
    return 0;
}