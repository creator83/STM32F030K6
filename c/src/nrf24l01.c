#include "nrf24l01.h"


void nrf24l01_init (void)
{
	//===Settings SPI===//
	init_spi_8 ();
	
	//===Settings pins===//
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//CE
	PORT->MODER &= ~GPIO_MODER_MODER2;
	PORT->OTYPER &= ~GPIO_OTYPER_OT_2;
	
	//IRQ
	PORT->MODER &= ~GPIO_MODER_MODER3;
	EXTI->IMR |= 1 << IRQ;
	EXTI->FTSR |= 1 << IRQ;
}

uint8_t nrf24l01_wr_register (uint8_t r_n_reg,uint8_t mask1, uint8_t mask2 )
{
	uint8_t r_regist=0;
  CS_CLEAR;
	//command for read register
  spi1_tx_8(mask1+r_n_reg);
	
	//read register
  r_regist = spi1_rx_8(mask2);
  nrf24l01_SET_CSN;//???????? ?????
  SREG=SR;
  return r_regist; //?????????? ???????? ????????		
}
