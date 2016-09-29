#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "Gpio.h"

/*
Usart1
TX : (PB6, AF0) (PA9, AF1)
RX : (PB7, AF0) (PA10, AF1)


*/

namespace UartDef
{
//===Defenitions===//
//Tx
const Gpio::Port TxPort = Gpio::A;
const uint8_t TxPin = 9;
const Gpio::Afmode TxAf = Gpio::AF1;

//Rx
const Gpio::Port RxPort = Gpio::A;
const uint8_t RxPin = 10;
const Gpio::Afmode RxAf = Gpio::AF1;	
}


#ifndef UART_H
#define UART_H

typedef unsigned int* reg;

class uart
{
//variables
public:
  enum baud {baud9600 = 9600 , baud57600 = 57600 , baud115200 = 115200};
private:
  Gpio Tx, Rx;
//functions
public:
  uart (baud b);
  void transmit (uint8_t data);
  void transmit (char * str);  
  uint8_t receive ();
private:
	
};



#endif
