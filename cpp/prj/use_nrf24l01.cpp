#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "spi.h"
#include "nrf24l01.h"
#include "uart.h"

Tact frq;
Spi spi0;
Uart uart1 (Uart::baud9600);

  extern "C"
  {
    void EXTI0_1_IRQHandler();
		
  }
	
void EXTI0_1_IRQHandler()
{
	EXTI->PR |= 1 << 1;
}

int main()
{
	Nrf24l01 radio (spi0);
	
	uart1.transmit (radio.readRegister (CONFIG));
	uart1.transmit ("\n");
	uart1.transmit (radio.readRegister (EN_AA));
	uart1.transmit (radio.readRegister (EN_RXADDR));
	uart1.transmit (radio.readRegister (SETUP_AW));
	uart1.transmit (radio.readRegister (SETUP_RETR));
	uart1.transmit (radio.readRegister (RF_CH));
	uart1.transmit (radio.readRegister (RF_SETUP));
	uart1.transmit (radio.readRegister (STATUS));
	uart1.transmit (radio.readRegister (OBSERVE_TX));
	uart1.transmit (radio.readRegister (CD));
	uart1.transmit (radio.readRegister (RX_ADDR_P0));
	uart1.transmit (radio.readRegister (RX_ADDR_P1));
	uart1.transmit (radio.readRegister (RX_ADDR_P2));
	uart1.transmit (radio.readRegister (RX_ADDR_P3));
	uart1.transmit (radio.readRegister (RX_ADDR_P4));
	uart1.transmit (radio.readRegister (RX_ADDR_P5));	
	uart1.transmit (radio.readRegister (TX_ADDR));
	uart1.transmit (radio.readRegister (RX_PW_P0));
	uart1.transmit (radio.readRegister (RX_PW_P1));
	uart1.transmit (radio.readRegister (RX_PW_P2));
	uart1.transmit (radio.readRegister (RX_PW_P3));
	uart1.transmit (radio.readRegister (RX_PW_P4));		
	uart1.transmit (radio.readRegister (RX_PW_P5));
	uart1.transmit (radio.readRegister (FIFO_STATUS));	

	//radio.sendByte (1);
	
  while (1)
  {
	
  }
}

