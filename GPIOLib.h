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
#ifndef GPIO_H
#define GPIO_H

enum GPIODirection 
{ 
  GPIO_IN=0,
  GPIO_OUT
};


enum GPIOValue
{ 
  GPIO_LOW=0,
  GPIO_HIGH
};


int GPIOInit(int PortNumber, int GPIOPinNumber);
int GPIOSetDir(int GPIO, int Direction);
int GPIOWriteValue(int GPIO, int Value);
int GPIOReadValue(int GPIO);

#endif
