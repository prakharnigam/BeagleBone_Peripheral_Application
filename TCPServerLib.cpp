/* fpont 12/99 */
/* pont.net    */
/* tcpClient.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int TCPServerInit(int TCPRequiredServerPort)
{
	int TCPServer_FD;

	int TCPSocket_FD, NewTCPSocket_FD;
	socklen_t clilen;
	char buffer[256];

	struct sockaddr_in serv_addr, cli_addr;

	/* create socket */
	TCPServer_FD = socket(AF_INET, SOCK_STREAM, 0);

	if(TCPServer_FD<0)
	{
		printf("ERROR: TCPServerInit-> Cannot open socket\n");
		return -1;
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(TCPRequiredServerPort);

	 if (bind(TCPSocket_FD, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	 {
		 printf("ERROR: TCPServerInit->ERROR on binding\n");
		 return -1;
	 }

    listen(TCPSocket_FD,5);
    clilen = sizeof(cli_addr);
    NewTCPSocket_FD = accept(TCPSocket_FD, (struct sockaddr *) &cli_addr, &clilen);

    if (NewTCPSocket_FD < 0)
    {
    	printf("ERROR: TCPServerInit->ERROR on accept\n");
    	return -1;
    }

	return NewTCPSocket_FD;

}

int TCPServerSendData(int TCPClient_FD, char * SendBuffer)
{
    int error = write(TCPClient_FD, SendBuffer, strlen(SendBuffer));

    if(error<0)
    {
    	printf("ERROR: TCPClientSendData->Cannot send data ");
		close(TCPClient_FD);
		return -1;
    }

    printf("TCPClientSendData->[%s]\n",SendBuffer);
}

int TCPServerReceiveData(int TCPServer_FD, char * RecieveBuffer, int RecieveBufferLen)
{
	 bzero(RecieveBuffer,256);
	 int Count = read(TCPServer_FD, RecieveBuffer, 255);
	 if (Count < 0)
	 {
		 printf("ERROR: TCPServerReceiveData->ERROR reading from socket");
		 return -1;
	 }

	 return Count;
}


int TCPServerClose(int TCPClient_FD)
{
	return close(TCPClient_FD);
}

