/* fpont 12/99 */
/* pont.net    */
/* tcpClient.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> /* close */
#include <string.h>


int TCPClientInit(void)
{
	int TCPClient_FD;

	/* create socket */
	TCPClient_FD = socket(AF_INET, SOCK_STREAM, 0);

	if(TCPClient_FD<0)
	{
		printf("ERROR: TCPClientInit-> Cannot open socket ");
		return -1;
	}

	return TCPClient_FD;

}


int TCPClientConnect(int TCPClient_FD, char* ServeripAddress, int ServerPort)
{

	struct hostent *HostHandler;
	struct sockaddr_in servAddr, localAddr;

	HostHandler = gethostbyname(ServeripAddress);
	if(HostHandler == NULL)
	{
		printf("ERROR: TCPClientConnect-> Unknown host '%s'\n",ServeripAddress);
		return -1;
	}

	servAddr.sin_family = HostHandler->h_addrtype;
	memcpy((char *) &servAddr.sin_addr.s_addr, HostHandler->h_addr_list[0], HostHandler->h_length);
	servAddr.sin_port = htons(ServerPort);


	/* bind any port number */
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);

	int rc = bind(TCPClient_FD, (struct sockaddr *) &localAddr, sizeof(localAddr));

	if(rc<0)
	{
		printf("ERROR: TCPClientConnect->%s: cannot bind port TCP %u\n",ServeripAddress, ServerPort);

	}


	/* connect to server */
	rc = connect(TCPClient_FD, (struct sockaddr *) &servAddr, sizeof(servAddr));
	if(rc<0)
	{
		printf("ERROR: TCPClientConnect->Cannot connect to Server\n");
		return -1;
	}

	return 1;

}

int TCPClientSendData(int TCPClient_FD, char * SendBufferPointer)
{
    int error = send(TCPClient_FD, SendBufferPointer, strlen(SendBufferPointer) + 1, 0);

    if(error<0)
    {
    	printf("ERROR: TCPClientSendData->Cannot send data ");
		close(TCPClient_FD);
		return -1;
    }

    printf("TCPClientSendData->[%s]\n",SendBufferPointer);
}

int TCPClientReceiveData(int TCPClient_FD, char * RecieveBuffer, int RecieveBufferLen)
{
	return recv(TCPClient_FD, RecieveBuffer, RecieveBufferLen, 0);
}


int TCPClientClose(int TCPClient_FD)
{
	return close(TCPClient_FD);
}

