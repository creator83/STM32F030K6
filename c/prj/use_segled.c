#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "delay.h"
#include "segled.h"
#include "encoder.h"


int main ()
{
	init_HSI ();
	init_PLL ();
	segled_init ();
	

	while(1)
	{
		buffer (4326);
		delay_ms (500);
	}

}
