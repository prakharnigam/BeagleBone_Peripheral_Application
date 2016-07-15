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

using namespace std;


struct GPIO
{
	int	 GPIOPIN;
	char setValue[4];
	char GPIOString[4];
	char GPIOValue[64];
	char GPIODirection[64];
	
}gpio[100];


int GPIOInit(int PortNumber, int GPIOPinNumber)
{
	//GPIOM_N--- GPIO1_28
	//Reference number = M*32 + N
	int GPIO = PortNumber*32 + GPIOPinNumber;
	gpio[GPIO].GPIOPIN = GPIO;
	sprintf(gpio[GPIO].GPIOString, "%d", gpio[GPIO].GPIOPIN);
    sprintf(gpio[GPIO].GPIOValue, "/sys/class/gpio/gpio%d/value", gpio[GPIO].GPIOPIN);
    sprintf(gpio[GPIO].GPIODirection, "/sys/class/gpio/gpio%d/direction", gpio[GPIO].GPIOPIN);
	
	return GPIO;
}

int GPIOSetDir(int GPIO, int Direction)
{
	// Export the pin
	FILE *myOutputHandle = NULL;
    if ((myOutputHandle = fopen("/sys/class/gpio/export", "ab")) == NULL){
        printf("Unable to export GPIO pin\n");
        return -1;
    }
    strcpy(gpio[GPIO].setValue, gpio[GPIO].GPIOString);
    fwrite(&gpio[GPIO].setValue, sizeof(char), 2, myOutputHandle);
    fclose(myOutputHandle);
 
    // Set direction of the pin to an output
    if ((myOutputHandle = fopen(gpio[GPIO].GPIODirection, "rb+")) == NULL){
        printf("Unable to open direction handle\n");
        return -1;
    }
	
	if(Direction == 1)
		strcpy(gpio[GPIO].setValue,"out");
	else if(Direction == 0)
		strcpy(gpio[GPIO].setValue,"in");
	else
		printf("SetGPIO: Enter appropriate direction in GPIO\n");
	
    fwrite(&gpio[GPIO].setValue, sizeof(char), 3, myOutputHandle);
    fclose(myOutputHandle);
	
	return GPIO;
}

int GPIOWriteValue(int GPIO, int Value)
{
	FILE *myOutputHandle = NULL;
	// Set output to high
	if ((myOutputHandle = fopen(gpio[GPIO].GPIOValue, "rb+")) == NULL){
		printf("Unable to open value handle\n");
		return -1;
	}
	
	if(Value == 1)
		strcpy(gpio[GPIO].setValue, "1"); // Set value high
	else if(Value == 0)
		strcpy(gpio[GPIO].setValue, "0"); // Set value lower_bound
	else
		printf("Enter proper value in SetGPIOValue(int GPIO, char Value)\n");
	
	
	fwrite(&gpio[GPIO].setValue, sizeof(char), 1, myOutputHandle);

	fclose(myOutputHandle);

	return 1;
}

int GPIOReadValue(int GPIO)
{
	FILE *myOutputHandle = NULL;
	int Value=0;
	// Set output to high
	if ((myOutputHandle = fopen(gpio[GPIO].GPIOValue, "rb+")) == NULL){
		printf("Unable to open value handle\n");
		return -1;
	}

	fread(&gpio[GPIO].setValue, sizeof(char), 1, myOutputHandle);

	fclose(myOutputHandle);

	if(strcmp (gpio[GPIO].setValue,"1n") == 0)
		Value = 1;
	else if(strcmp (gpio[GPIO].setValue,"0n") == 0)
		Value = 0;
	else
		printf("Error: GPIOReadValue");

	return Value;

}
