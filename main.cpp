/*******************************************************
* Library for digital output on a GPIO pin
* on the new beaglebone black running the
* Linux Angstrom distribution.
* 
* 
* 
* 
* 
********************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "GPIOLib.h"
#include "UARTLib.h"
#include "SPILib.h"
#include "TCPClientLib.h"
#include "TCPServerLib.h"

using namespace std;
 
int main(int argc, char** argv) {

	////////////////////////////// GPIO INIT ///////////////////////////////////////
	int YellowLED = GPIOInit(1, 28);
	GPIOSetDir(YellowLED, GPIO_OUT);
	GPIOWriteValue(YellowLED, GPIO_LOW);
	
	int GPIO1_17 = GPIOInit(1, 17);
	GPIOSetDir(GPIO1_17, GPIO_IN);
	///////////////////////////////////////////////////////////////////////////////

	////////////////////////////  UART INIT ///////////////////////////////////////

	int uart1 = UARTInit(UART1, UARTBAUD_115200);
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////  SPI INIT  ////////////////////////////////////////

	int spi1= SPIInit();
	SPIConfiguration(spi1, SPIMODE_0, 8, 400000);
	///////////////////////////////////////////////////////////////////////////////

	//////////////////////////  TCP CLIENT INIT  //////////////////////////////////
	int tcpclient = TCPClientInit();
	///////////////////////////////////////////////////////////////////////////////

	//////////////////////////  TCP SERVER INIT  //////////////////////////////////
	int tcpserver = TCPServerInit(8080);
	///////////////////////////////////////////////////////////////////////////////

	while (1)
	{
		///////////////////////  GPIO APPLICATION //////////////////////////////////

		int GPIOVALUE = GPIOReadValue(GPIO1_17);
		printf("GPIO Read Value = %d", GPIOVALUE);
		GPIOWriteValue(YellowLED, GPIOVALUE);

		///////////////////////////////////////////////////////////////////////////

		//////////////////////  UART APPLICATION  /////////////////////////////////

		char WriteBuffer[] = "Hello in am Printing\n";
		UARTWriteString(uart1, WriteBuffer);
		printf("The received uart2 data is [%c]\r\n", UARTRead(uart1));

		//////////////////////////////////////////////////////////////////////////


		////////////////////  SPI APPLICATION  //////////////////////////////////

		char tx[] = {
			0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF,
			0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
			0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
			0x07, 0x08, 0x09, 0x10, 0x11, 0x12,
			0xDE, 0xAD, 0xBE, 0xEF, 0xBA, 0xAD,
		};
		SPIWrite(spi1, tx);

		char rx[38] = {0, };

		SPIRead(spi1, rx, 36);

		int PrintCount;
		for (PrintCount = 0; PrintCount < 36; PrintCount++) {
			if (!(PrintCount % 6))
				puts("");
			printf("%.2X ", rx[PrintCount]);
		}

		puts("");

		/////////////////////////////////////////////////////////////////////////

		/////////////////  TCP CLIENT APPLICATION  //////////////////////////////
		TCPClientConnect(tcpclient, "172.24.120.152" , 2000);
		TCPClientSendData(tcpclient, "Hey data is here\n");
		// Note program will wait for receive data
		char TCPReceiveData[50];
		TCPClientReceiveData(tcpclient, TCPReceiveData, 20);
		printf("----- TCPClientReceiveData ----------\n");
		printf("%s",TCPReceiveData);
		printf("\n-----------------------------------\n");
		/////////////////////////////////////////////////////////////////////////


		/////////////////  TCP CLIENT APPLICATION  //////////////////////////////

		// Note program will wait for receive data
		char ServerReceiveData[50];
		TCPServerReceiveData(tcpserver, ServerReceiveData, 20);
		printf("Here is the message: %s\n",ServerReceiveData);
		TCPServerSendData(tcpserver, "Server Data\n");
		/////////////////////////////////////////////////////////////////////////


		sleep(1);
	}


	TCPClientClose(tcpclient);

	return 0;
}
