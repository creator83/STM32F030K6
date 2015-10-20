#include "stm32f0xx.h"                  // Device header
#define F_CPU 48000000

#ifndef DELAY_H
#define DELAY_H


 void delay_ms(uint16_t delay);
 void delay_us(uint16_t delay);
 
#endif
