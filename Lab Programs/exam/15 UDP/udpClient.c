#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <unistd.h>
#include<arpa/inet.h>


int main(void){
	
	int clientSocket, n;
	socklen_t addr_size;
	struct sockaddr_in serverAddr;
	char buffer[81];

	// setp 1: create UDP client socket
	clientSocket = socket( AF_INET, SOCK_DGRAM, 0);

	// configure settings in server address struct
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(5000);


	// initialize size variable to be used later on
	addr_size = sizeof(serverAddr);

	while(1) {
		// send message to server
		printf("type a sentence to send to server : ");
		fgets(buffer, 81, stdin);
		//printf("you typed : %s", buffer);
	
		n = strlen(buffer) + 1;

		// sned mesaage to server
		sendto(clientSocket, buffer, n, 0, (struct sockaddr*)&serverAddr, addr_size);
		if ((strncmp("exit", buffer, 4) == 0) || n == 1)
			break;
			
		printf("waiting for the server to reply...\n");

		// recieve message from server
		n = recvfrom(clientSocket, buffer, 81, 0, (struct sockaddr*)&serverAddr, &addr_size);

		printf("revieved from server : %s\n", buffer);
	}

	close(clientSocket);
	return 0;
}


//gcc udpClient.c -o udpClient && ./udpClient