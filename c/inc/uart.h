#include "stm32f0xx.h"                  // Device header
#include "delay.h"

#define BAUD 9600
#define BRR_VAL F_CPU/BAUD

#define TX 9;
#define RX 10;


#ifndef UART_H
#define UART_H

  void uart_init (void);
  void transmit_byte (uint8_t data);
  void transmit_string (char * str);  




#endif

