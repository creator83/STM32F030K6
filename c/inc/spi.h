#include "stm32f0xx.h"                  // Device header

#define CS 4
#define CS_CLEAR GPIOA->ODR &= ~(1 << CS)
#define CS_SET GPIOA->ODR |= (1 << CS)


#ifndef SPI_H
#define SPI_H
 
void init_spi_8 (void);

void init_spi_16 (void);

void spi1_tx_8 (uint8_t data);

uint16_t spi1_rx_16 (void);

uint8_t spi1_rx_8 (void);

uint8_t spi1_exchange_8 (uint8_t data);

void set_cs (void);
 
void clear_cs (void);

#endif
