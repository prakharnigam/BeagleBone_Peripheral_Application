/*******************************************************
* Library for UART control.
* 
* 
* 
* 
********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h> // needed for memset
#include "UARTLib.h"


// UART pin mux Values
#define UART1_PINMUX_RX		"20"
#define UART1_PINMUX_TX		"0"

#define UART2_PINMUX_RX		"21"
#define UART2_PINMUX_TX		"1"

#define UART4_PINMUX_RX		"26"
#define UART4_PINMUX_TX		"6"

#define UART5_PINMUX_RX		"24"
#define UART5_PINMUX_TX		"4"
////////////////////////////////

using namespace std;

struct termios UARTConfiguration[5];

int UARTInit(int UARTPort, int UARTBaudRate)
{

	int tty_fd;

	UARTSetpinMux(UARTPort);

	memset(&UARTConfiguration[UARTPort],0,sizeof(UARTConfiguration[UARTPort]));

	UARTConfiguration[UARTPort].c_iflag=IGNPAR | ICRNL;
	UARTConfiguration[UARTPort].c_oflag=0;
	UARTConfiguration[UARTPort].c_cflag=CS8|CREAD|CLOCAL;           // 8n1
	UARTConfiguration[UARTPort].c_lflag=0;
	UARTConfiguration[UARTPort].c_cc[VMIN]=1;
	UARTConfiguration[UARTPort].c_cc[VTIME]=5;


	// Opening port for communication.
	switch(UARTPort)
	{
	case UART1:
		tty_fd=open("/dev/ttyO1", O_RDWR | O_NONBLOCK);
		break;
	case UART2:
		tty_fd=open("/dev/ttyO2", O_RDWR | O_NONBLOCK);
		break;
	case UART4:
		tty_fd=open("/dev/ttyO4", O_RDWR | O_NONBLOCK);
		break;
	case UART5:
		tty_fd=open("/dev/ttyO5", O_RDWR | O_NONBLOCK);
		break;
	default:
		printf("ERROR: UARTPort selected is not available\r\n");
		break;
	}

	if (tty_fd < 0)
	{
			printf("ERROR: Port %d can't be open\r\n", UARTPort);
			exit(EXIT_FAILURE);
	}

	cfsetospeed(&UARTConfiguration[UARTPort],UARTBaudRate);      // Enter Baud rate from enum list
	cfsetispeed(&UARTConfiguration[UARTPort],UARTBaudRate);      // Enter Baud rate from enum list

	tcsetattr(tty_fd,TCSANOW,&UARTConfiguration[UARTPort]);


	return tty_fd;
}


int UARTSetpinMux(int UARTPort)
{
	FILE *UARTFileHandler = NULL;

	//Setting Pin as UART
	switch(UARTPort)
	{
	case UART1:

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/uart1_rxd", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART1_PINMUX_RX, sizeof(char), 2, UARTFileHandler);
		fclose(UARTFileHandler);

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/uart1_txd", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART1_PINMUX_TX, sizeof(char), 1, UARTFileHandler);
		fclose(UARTFileHandler);

		break;
	case UART2:

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/spi0_sclk", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART2_PINMUX_RX, sizeof(char), 2, UARTFileHandler);
		fclose(UARTFileHandler);

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/spi0_d0", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART2_PINMUX_TX, sizeof(char), 1, UARTFileHandler);
		fclose(UARTFileHandler);

		break;
	case UART4:

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/gpmc_wait0", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART4_PINMUX_RX, sizeof(char), 2, UARTFileHandler);
		fclose(UARTFileHandler);

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/gpmc_wpn", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART4_PINMUX_TX, sizeof(char), 1, UARTFileHandler);
		fclose(UARTFileHandler);

		break;
	case UART5:

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/lcd_data9", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART5_PINMUX_RX, sizeof(char), 2, UARTFileHandler);
		fclose(UARTFileHandler);

		if ((UARTFileHandler = fopen("/sys/kernel/debug/omap_mux/lcd_data8", "ab")) == NULL){
				printf("Unable to export GPIO pin\n");
				return -1;
			}
		fwrite(UART5_PINMUX_TX, sizeof(char), 1, UARTFileHandler);
		fclose(UARTFileHandler);

		break;
	default:
		printf("ERROR: UARTPort selected is not available\r\n");
		break;
	}

	return 1;

}

int UARTWriteByte(int UARTtty_FD,  char Byte)
{

	write(UARTtty_FD,&Byte, 1);
	return 1;

}


int UARTWriteString(int UARTtty_FD,  char *String)
{
	while(*String)
	{
		write(UARTtty_FD,String, 1);
		*String++;
	}

	return 1;

}

char UARTRead(int UARTtty_FD)
{
	char data;

	if(read(UARTtty_FD,&data,1)>0)
		return data;
	else
		return 0;

}


int UARTClose(int UARTtty_FD)
{
	close(UARTtty_FD);
	return 1;
}
