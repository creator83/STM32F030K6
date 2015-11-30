#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "delay.h"
#include "ili9325.h"



int main ()
{
	ili9325_init ();
	ili9325_fill_screen (RED);
	
	while (1)
	{
		
	}	
}




