#include "stm32f0xx.h"                  // Device header
#include "delay.h"
#include "spi.h"
#include "nrf24l01registors.h"

#define PORT GPIOA

#define IRQ 3
#define CE 2

#define CE_CLEAR PORT->ODR &= ~(1 << CE)
#define CE_SET PORT->ODR |= (1 << CE)

#ifndef NRF24L01_H
#define NRF24L01_H

void nrf24l01_init (void);


#endif
