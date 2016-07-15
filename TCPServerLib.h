/*******************************************************
* Library for UART control.
* 
* 
* 
* 
********************************************************/
#ifndef TCP_SERVER_LIB_H
#define TCP_SERVER_LIB_H

/*
 * TCPClientInit description
 * This routine is use for initialization TCP port which is available on board.
 *
 *
 * @return		TCPClient_FD	The int will return the File descriptor for each TCP initialization.
 */
int TCPServerInit(int TCPRequiredServerPort);


/*
 * UARTWriteString description
 * This routine is use for transmit string on UART
 *
 * @param		UARTtty_FD		The unique id return form routine UARTInit() need to pass in this argument.
 *
 * @param		String			Type string need to transmit over UART
 *
 * @return		int				Returns as true if successful return.
 *
 */
int TCPServerSendData(int TCPClient_FD, char * SendBuffer);
int TCPServerReceiveData(int TCPServer_FD, char * RecieveBuffer, int RecieveBufferLen);

/*
 * UARTClose description
 * This routine is use to close UART port.
 *
 * @param		UARTtty_FD		The unique id return form routine UARTInit() need to pass in this argument.
 *
 * @return		int				Returns as true if successfully close the UART port.
 *
 */
int TCPServerClose(int TCPClient_FD);


#endif
