#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>


int main(void){
	
	int udpSocket, n, i;
	char buffer[81];
	struct sockaddr_in serverAddr, clientAddr;

	socklen_t addr_size, client_addr_size;

	// setp 1: create UDP server socket
	udpSocket = socket( AF_INET, SOCK_DGRAM, 0);

	// configure settings in server address struct
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(5000);

	// bind socket with address struct
	bind(udpSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	// initialize size variable to be used later on
	addr_size = sizeof(clientAddr);
	printf("server is running...\n");
	while(1){ 
		// trying to recieve any incoming UDP datagram.
		// Address and port of requesting client will be stored on client variable.
		n = recvfrom(udpSocket, buffer, 80, 0, (struct sockaddr*)&clientAddr, &addr_size);
		
		if ((strncmp("exit", buffer, 4) == 0) || n == 1)
			break;
		// conert message recieved to uppder case 
		for(i = 0; i < n-1; i++)
			buffer[i] = toupper(buffer[i]);
		
		// send uppercase message back to client using client as the address
		sendto(udpSocket, buffer, n, 0, (struct sockaddr*)&clientAddr, addr_size);

	}

	printf("\nserver exiting...\n");

	return 0;
}


// gcc udpServer.c -o udpServer && ./udpServer