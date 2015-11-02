#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "Gpio.h"


#ifndef UART_H
#define UART_H

typedef unsigned int* reg;

class uart
{
//variables
public:
  enum baud {baud9600 = 9600 , baud57600 = 57600 , baud115200 = 115200};
private:
  Gpio pin;
  enum pin_def {TX = 9 , RX};
//functions
public:
  uart (baud b);
  void transmit (uint8_t data);
  void transmit (char * str);  
  uint8_t receive ();
};



#endif
