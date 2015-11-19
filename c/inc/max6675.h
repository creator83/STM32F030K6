#include "stm32f0xx.h"                  // Device header
#include "delay.h"


//#define Decimal
#define SPI_16

//Pins for Soft Spi
#define sclk 5
#define miso 6
#define cs 4

#ifndef MAX6675_H
#define MAX6675_H


void max6675_init (void);

#ifdef Decimal
double readCelsius(void);

#else
uint16_t readCelsius(void);


#endif

#endif
