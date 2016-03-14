#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "Spi.h"
#include "nrf24l01.h"
#include "uart.h"


tact frq;

 /* 
  extern "C"
  {
    void EXTI0_1_IRQHandler();
  }*/

int main()
{
	uart uart1 (uart::baud9600);
	nrf24l01 radio;
	uint8_t v = radio.read_register (CONFIG);
	for (uint8_t i=0;i<8;++i)
		{
			if (v&(1 << (7-i))) uart1.transmit ('1');
			else uart1.transmit ('0');
		}
		
		delay_ms (2000);
		uart1.transmit ("===");
		radio.sc_bit(CONFIG, PRIM_RX, 1);
		v = radio.read_register (CONFIG);
		for (uint8_t i=0;i<8;++i)
		{
			if (v&(1 << (7-i))) uart1.transmit ('1');
			else uart1.transmit ('0');
		}	
		
		
  while (1)
  {
		
  }
}
