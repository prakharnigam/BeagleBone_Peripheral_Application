/*******************************************************
* Library for UART control.
* 
* 
* 
* 
********************************************************/
#ifndef TCP_CLIENT_LIB_H
#define TCP_CLIENT_LIB_H

/*
 * TCPClientInit description
 * This routine is use for initialization TCP port which is available on board.
 *
 *
 * @return		TCPClient_FD	The int will return the File descriptor for each TCP initialization.
 */
int TCPClientInit(void);

/*
 * UARTSetpinMux description
 * This routine is use for set controller pin mux according to UART.
 *
 * @param		UARTPort		Port name of UART which need to initialize, this param are
 * 								already in enum UARTPort enum UARTPort{UART1=1, UART2, UART4, UART5}
 *
 * @return						The routine return as true after successfully pin set,
 * 								and returns negative value if the pin mux is unsuccessful
 *
 */
int TCPClientConnect(int TCPClient_FD, char* ServeripAddress, int ServerPort);


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
int TCPClientSendData(int TCPClient_FD, char * SendBufferPointer);


/*
 * UARTClose description
 * This routine is use to close UART port.
 *
 * @param		UARTtty_FD		The unique id return form routine UARTInit() need to pass in this argument.
 *
 * @return		int				Returns as true if successfully close the UART port.
 *
 */
int TCPClientClose(int TCPClient_FD);

int TCPClientReceiveData(int TCPClient_FD, char * RecieveBuffer, int RecieveBufferLen);

#endif
