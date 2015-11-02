#include "stm32f0xx.h"                  // Device header

#define CS 4


#ifndef SPI_H
#define SPI_H
 
void init_spi_8 (void);

void init_spi_16 (void);

uint8_t transfer (uint8_t data);

uint16_t spi1_rx (void);

void set_cs (void);
 
void clear_cs (void);

#endif
