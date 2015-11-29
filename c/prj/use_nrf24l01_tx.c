#include "stm32f0xx.h"                  // Device header
//#include "uart.h"
#include "tact.h"
#include "delay.h"
#include "segled.h"
#include "nrf24l01.h"


#define F_CPU 48000000
#define tick 1000
#define systick_ms 1
#define systick_val (F_CPU/tick)*systick_ms
#define button_ 1



int main ()
{
	uint8_t i;

	nrf24l01_init (0x03);
	nrf24l01_RX_TX_mode(PRX);
	
	while (1)
	{
		
		nrf24l01_FLUSH_TX;
		nrf24l01_Sent_data_Ret(i);
		i+=1;
		delay_ms (1000);
	}
	
}

