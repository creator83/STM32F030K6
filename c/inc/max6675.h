#include "stm32f0xx.h"                  // Device header
#include "delay.h"

//Soft Spi
//#define SOFTSPI
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

void max6675_buffer (double val);

#else
uint16_t readCelsius(void);

//void max6675_buffer (uint16_t val);

//uint16_t division (uint16_t n);
/*
struct divmod10_t
{
    uint32_t quot;
    uint8_t rem;
};*/

#endif

#endif
