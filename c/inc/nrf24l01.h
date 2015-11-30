#include "stm32f0xx.h"                  // Device header
#include "delay.h"
#include "spi.h"
#include "nrf24l01registors.h"

#define PORT GPIOA

#define IRQ 10
#define CE 9

#define CE_CLEAR PORT->ODR &= ~(1 << CE)
#define CE_SET PORT->ODR |= (1 << CE)


#ifndef NRF24L01_H
#define NRF24L01_H

void nrf24l01_init (void);
uint8_t nrf24l01_write_register (uint8_t reg,uint8_t data);
uint8_t nrf24l01_read_register (uint8_t reg);
unsigned char nrf24l01_command (unsigned char M_ask);
uint8_t nrf24l01_sc_bit (unsigned char reg,unsigned char register_bit,char W);
void nrf24l01_RX_mode (void);
void nrf24l01_TX_mode (void);

void nrf24l01_write_data (unsigned char data);
void nrf24l01_Send_byte (uint8_t data);
unsigned char nrf24l01_read_data (void) ;


#endif
