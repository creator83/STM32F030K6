#include "stm32f0xx.h"

#define BAUD 9600
#ifndef UART_H
#define UART_H

void Usart0_init (void);

void transmit_byte (uint8_t data);

void transmit_string (char * str);

#endif
