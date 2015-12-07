#include "stm32f0xx.h"                  // Device header
#include "delay.h"


//#define Decimal

#define SOFTSPI
#define PORT_ GPIOB
#define cs 6
#define sck 3
#define miso 4

#ifndef MAX6675_H
#define MAX6675_H


void max6675_init (void);

#ifdef Decimal
double readCelsius(void);


#else
uint16_t readCelsius(void);


#endif

#endif
