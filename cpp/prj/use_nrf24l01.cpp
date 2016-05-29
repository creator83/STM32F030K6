#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "Spi.h"
#include "nrf24l01.h"
#include "pcd8544.h"


	tact frq;
	nrf24l01 radio;
	pcd8544 lcd;
	const char led = 0;
	Gpio B (Gpio::B);

  extern "C"
  {
    void EXTI0_1_IRQHandler();
		
  }
	
void EXTI0_1_IRQHandler()
{
	EXTI->PR |= 1 << 1;
	uint8_t status = radio.get_status ();
	radio.w_reg (STATUS, status);

	B.setPin (led);
}

int main()
{
	B.setOutPin (led);

	if (radio.startup) lcd.string_screen (0,0,"STARTUP OK");
	else lcd.string_screen (0,0,"STARTUP ERROR");
	//lcd.bin_number (35,1,radio.r_reg(CONFIG));
	/*for (uint8_t i=0;i<5;++i)
	uart1.transmit (radio.r_reg(CONFIG));

	uart1.transmit (radio.r_reg(EN_AA));

		uart1.transmit (radio.r_reg(FIFO_STATUS));

		radio.w_tx_buffer (125);

		uart1.transmit (radio.r_reg(FIFO_STATUS));
		delay_ms (500);
		radio.command (FLUSH_RX);
		delay_ms (500);
		uart1.transmit (radio.r_reg(FIFO_STATUS));
		delay_ms (500);
		radio.command (FLUSH_TX);
		delay_ms (500);
		uart1.transmit (radio.r_reg(FIFO_STATUS));
		delay_ms (500);
		uart1.transmit (radio.r_reg(FEATURE));*/
	/*
	uart1.transmit("===");
	for (uint8_t i=0;i<5;++i)
	{
		uart1.transmit (radio.get_status());
		delay_ms (500);
	}
		for (uint8_t i=0;i<5;++i)
	{
		uart1.transmit (radio.r_reg(CONFIG));
		delay_ms (500);
	}	
	//radio.change_bit (CONFIG, MASK_RX_DR, 1);
	
		for (uint8_t i=0;i<5;++i)
	{
		uart1.transmit (radio.r_reg(CONFIG));
		delay_ms (500);
	}		
	radio.rx_state ();*/
  while (1)
  {
	
  }
}

