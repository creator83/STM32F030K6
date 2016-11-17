#include "stm32f0xx.h"
#include "tact.h"
#include "hd44780.h"





Tact frq;

int main()
{
	Hd44780 lcd;
	lcd.setPosition (0, 0);
	lcd.sendString ("Heat Gun");
	
	while (1)
	{
		
	}
}
