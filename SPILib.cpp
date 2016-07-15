/*******************************************************
* Library for SPI control.
* 
* 
* 
* 
********************************************************/

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))


static const char *device = "/dev/spidev2.0";


spi_ioc_transfer SPIHandler;

using namespace std;

uint8_t spi_mode = 0;
static uint8_t spi_bits = 8;
static uint32_t spi_speed = 500000;
static uint16_t delay;


int SPIInit(void)
{
	int SPI_FD = open(device, O_RDWR);
	if (SPI_FD < 0)
		printf("ERROR: SPI can't open device");

	/*
	 * spi mode
	 */
	int ret = ioctl(SPI_FD, SPI_IOC_WR_MODE, &spi_mode);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't set spi mode\n");

	ret = ioctl(SPI_FD, SPI_IOC_RD_MODE, &spi_mode);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't get spi mode\n");

	/*
	 * bits per word
	 */
	ret = ioctl(SPI_FD, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't set bits per word\n");

	ret = ioctl(SPI_FD, SPI_IOC_RD_BITS_PER_WORD, &spi_bits);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't get bits per word\n");

	/*
	 * max speed hz
	 */
	ret = ioctl(SPI_FD, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't set max speed hz\n");

	ret = ioctl(SPI_FD, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't get max speed hz\n");

	return SPI_FD;
}

int SPIConfiguration(int SPI_FD, char SPIMode, char SPIbits, int SPISpeed)
{

	spi_mode = SPIMode;
	spi_bits = SPIbits;
	spi_speed = SPISpeed;


	/*
	 * spi mode
	 */
	int ret = ioctl(SPI_FD, SPI_IOC_WR_MODE, &spi_mode);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't set spi mode\n");

	ret = ioctl(SPI_FD, SPI_IOC_RD_MODE, &spi_mode);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't get spi mode\n");

	/*
	 * bits per word
	 */
	ret = ioctl(SPI_FD, SPI_IOC_WR_BITS_PER_WORD, &spi_bits);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't set bits per word\n");

	ret = ioctl(SPI_FD, SPI_IOC_RD_BITS_PER_WORD, &spi_bits);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't get bits per word\n");

	/*
	 * max speed hz
	 */
	ret = ioctl(SPI_FD, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't set max speed hz\n");

	ret = ioctl(SPI_FD, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);

	if (ret == -1)
		printf("ERROR: SPIConfiguration->can't get max speed hz\n");

	printf("------- SPI CONFIGURATION -------\n");
	printf("spi mode: %d\n", spi_mode);
	printf("bits per word: %d\n", spi_bits);
	printf("max speed: %d Hz (%d KHz)\n", spi_speed, spi_speed/1000);

	return 1;

}

void SPIWrite(int SPI_FD, char * SPIWriteBuffer)
{

	SPIHandler.tx_buf = (unsigned long)SPIWriteBuffer;
	SPIHandler.len = ARRAY_SIZE(SPIWriteBuffer);
	SPIHandler.delay_usecs = delay;
	SPIHandler.speed_hz = spi_speed;
	SPIHandler.bits_per_word = spi_bits;


	int ret = ioctl(SPI_FD, SPI_IOC_MESSAGE(1), &SPIHandler);

	if (ret < 1)
		printf("can't send spi message");

}

void SPIRead(int SPI_FD, char * SPIReadBuffer, int SizeofBuffer)
{
	SPIHandler.rx_buf = (unsigned long)SPIReadBuffer;
	SPIHandler.len = SizeofBuffer;
	SPIHandler.delay_usecs = delay;
	SPIHandler.speed_hz = spi_speed;
	SPIHandler.bits_per_word = spi_bits;

	int ret = ioctl(SPI_FD, SPI_IOC_MESSAGE(1), &SPIHandler);

	if (ret < 1)
		printf("can't send spi message");

}


int SPIClose(int SPI_FD)
{
	close(SPI_FD);
}
