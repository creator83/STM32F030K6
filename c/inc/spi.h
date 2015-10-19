#include "stm32f0xx.h"                  // Device header

#define CS 4


#ifndef SPI_H
#define SPI_H
 
void init_spi (void);

uint8_t transfer (uint8_t data);

void set_cs (void);
 
void clear_cs (void);

#endif
