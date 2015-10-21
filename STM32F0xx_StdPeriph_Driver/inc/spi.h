#include "stm32f0xx.h"

#ifndef SPI_H
#define SPI_H

#define CS_SET() GPIO_SetBits (GPIOA, GPIO_Pin_4)
#define CS_CLEAR() GPIO_ResetBits (GPIOA, GPIO_Pin_4)

void spi1_init (void);

void tx_byte (uint8_t data);

uint8_t rx_byte (void);

#endif
