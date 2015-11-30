#include "nrf24l01.h"


void nrf24l01_init (void)
{
	//===Settings SPI===//
	init_spi_8 ();
	
	//===Settings pins===//
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//CE
	PORT->MODER &= ~GPIO_MODER_MODER9;
	PORT->OTYPER &= ~GPIO_OTYPER_OT_9;
	
	//IRQ
	PORT->MODER &= ~GPIO_MODER_MODER10;
	EXTI->IMR |= 1 << IRQ;
	EXTI->FTSR |= 1 << IRQ;
	NVIC_EnableIRQ (EXTI4_15_IRQn);
	
	//===Setup NRF24L01===//
	
	//Delay after power on
  delay_ms(12);
	
	//Set PWR_UP bit
	nrf24l01_sc_bit (CONFIG, PWR_UP, 1);
  //Delay start up state
	delay_ms(2);
}
	


uint8_t nrf24l01_write_register (uint8_t reg,uint8_t data)
{
	uint8_t value;	
	clear_cs();
  
	//command for write registor
  spi1_tx_8(W_REGISTER+reg);
	
	//write register
  value = spi1_exchange_8 (data);
  set_cs();
	return value;
}

uint8_t nrf24l01_read_register (uint8_t reg)
{
	uint8_t value;	
	clear_cs();
	//command for write registor
  spi1_tx_8(W_REGISTER+reg);
	value = spi1_exchange_8 (NOP);
	return value;
}

uint8_t nrf24l01_sc_bit (unsigned char reg,unsigned char register_bit, char state)
{
	uint8_t reg_val = nrf24l01_read_register (reg);
	uint8_t value;	
	clear_cs();
  
	//command for write registor
  spi1_tx_8(W_REGISTER+reg);
	
	if (state)
	{
		//write register
		value = spi1_exchange_8 (reg_val|(1 << register_bit));
	}
	else
	{
		//write register
		value = spi1_exchange_8 (reg_val&~(1<<register_bit));
	}
  set_cs();
	return value;
}

void nrf24l01_RX_mode (void)
{
	nrf24l01_sc_bit (CONFIG, PRIM_RX, 1);
	CE_SET;
	delay_us (135);
}

void nrf24l01_TX_mode (void)
{
	nrf24l01_sc_bit (CONFIG, PRIM_RX, 0);
	CE_SET;	
	delay_us (15);
	CE_CLEAR;
	delay_us (135);
}

void nrf24l01_Send_byte (uint8_t data)
{
	nrf24l01_write_register (W_TX_PAYLOAD, data);
	nrf24l01_TX_mode();
	
}




