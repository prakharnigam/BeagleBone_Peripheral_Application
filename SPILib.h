/*******************************************************
* Library for SPI control.
* 
* 
* 
* 
********************************************************/
#ifndef SPILIB_H
#define SPILIB_H

#include <linux/types.h>
#include <linux/spi/spidev.h>


/* SPIMode
 * This enum is use to pass argument SPIMode
 * in function int SPIConfiguration(int SPI_FD, char SPIMode, char SPIbits, int SPISpeed);
 * where modes are standard Mode of SPI. i.e. MODE0, MODE1, MODE2 and MODE3
 */
enum SPIMode
{
	SPIMODE_0 = (0|0),
	SPIMODE_1 = (0|SPI_CPHA),
	SPIMODE_2 = (SPI_CPOL|0),
	SPIMODE_3 = (SPI_CPOL|SPI_CPHA),

};


/*
 * SPIInit description
 * This routine is use for initialization of required SPI which is available on board.
 *
 * @return		int				The int will return the unique id for each SPI initialization.
 */
int SPIInit(void);



/*
 * SPIConfiguration description
 * This routine is use configure SPI device driver.
 *
 * @param		SPI_FD			The unique id return form routine SPIInit() need to pass in this argument.
 *
 * @param		SPIMode			SPI Mode name which need to initialize, this param are
 * 								already in enum SPIMode enum SPIMode{SPIMODE_0, SPIMODE_1, SPIMODE_2, SPIMODE_3}
 *
 * @param		SPIbits			Pass number of bits in one message frame e.g. 8
 *
 * @param		SPISpeed		Define required SPI speed in Hz for communication e.g. 500000 for 500kHz SPI speed
 *
 * @return		int				Returns as true if successful return.
 *
 */
int SPIConfiguration(int SPI_FD, char SPIMode, char SPIbits, int SPISpeed);



/*
 * SPIWrite description
 * This routine is use for transmit buffer on SPI.
 *
 * @param		SPI_FD			The unique id return form routine SPIInit() need to pass in this argument.
 *
 * @param		SPIWriteBuffer	Type Buffer pinter need to transmit over SPI
 *
 * @return		int				Returns as true if successful return.
 *
 */
void SPIWrite(int SPI_FD, char * SPIWriteBuffer);


/*
 * SPIRead description
 * This routine is use for read buffer from SPI.
 *
 * @param		SPI_FD			The unique id return form routine SPIInit() need to pass in this argument.
 *
 * @param		SPIReadBuffer	Type Buffer pinter need to receive from SPI
 *
 * @param		SizeofBuffer	Size of receive  data buffer from SPI.
 *
 * @return		int				Returns as true if successful return.
 *
 */
void SPIRead(int SPI_FD, char * SPIReadBuffer, int SizeofBuffer);


/*
 * SPIClose description
 * This routine is use to close SPI port.
 *
 * @param		SPI_FD			The unique id return form routine SPIInit() need to pass in this argument.
 *
 * @return		int				Returns as true if successfully close the SPI port.
 *
 */
int SPIClose(int SPI_FD);


#endif
