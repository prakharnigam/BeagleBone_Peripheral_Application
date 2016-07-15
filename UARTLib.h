/*******************************************************
* Library for UART control.
* 
* 
* 
* 
********************************************************/
#ifndef UARTLIB_H
#define UARTLIB_H

#include <termios.h>

/* UARTPort
 * This enum is define available UART ports.
 */
enum UARTPort
{ 
  UART1=1,
  UART2,
  UART4,
  UART5

};

/* UARTBaudrate
 * This enum is used to set required baud rate
 * as per the application requirements.
 */
enum UARTBaudrate
{
  UARTBAUD_110 = B110,
  UARTBAUD_134 = B134,
  UARTBAUD_150 = B150,
  UARTBAUD_200 = B200,
  UARTBAUD_300 = B300,
  UARTBAUD_600 = B600,
  UARTBAUD_1200 = B1200,
  UARTBAUD_1800 = B1800,
  UARTBAUD_2400 = B2400,
  UARTBAUD_4800 = B4800,
  UARTBAUD_9600 = B9600,
  UARTBAUD_19200 = B19200,
  UARTBAUD_38400 = B38400,
  UARTBAUD_57600 = B57600,
  UARTBAUD_115200 = B115200,
  //UARTBAUD_128000 = B128000,
  UARTBAUD_230400 = B230400,
  //UARTBAUD_256000 = B256000,
  UARTBAUD_460800 = B460800,
  UARTBAUD_500000 = B500000,

};


/*
 * UARTInit description
 * This routine is use for initialization of required UART port which is available on board.
 *
 * @param		UARTPort		Port name of UART which need to initialize, this param are
 * 								already in enum UARTPort enum UARTPort{UART1=1, UART2, UART4, UART5}
 *
 * @param		UARTBaudRate	Pass required baud rate using enum UARTBaudrate, e.g. UARTBAUD_9600 for 9600
 *
 * @return		tty_fd			the int will return the unique id for each UART initialization.
 */
int UARTInit(int UARTPort, int UARTBaudRate);

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
int UARTSetpinMux(int UARTPort);


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
int UARTWriteString(int UARTtty_FD,  char *String);



/*
 * UARTWriteByte description
 * This routine is use for transmit string on UART
 *
 * @param		UARTtty_FD		The unique id return form routine UARTInit() need to pass in this argument.
 *
 * @param		Byte			Byte value need to transmit over UART
 *
 * @return		int				Returns as true if successful return.
 *
 */
int UARTWriteByte(int UARTtty_FD,  char Byte);

/*
 * UARTRead description
 * This routine is use to receive data from UART
 *
 * @param		UARTtty_FD		The unique id return form routine UARTInit() need to pass in this argument.
 *
 * @return		char			Returns received character
 *
 */
char UARTRead(int UARTtty_FD);


/*
 * UARTClose description
 * This routine is use to close UART port.
 *
 * @param		UARTtty_FD		The unique id return form routine UARTInit() need to pass in this argument.
 *
 * @return		int				Returns as true if successfully close the UART port.
 *
 */
int UARTClose(int UARTtty_FD);



#endif
