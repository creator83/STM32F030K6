#include "stm32f0xx.h"
#include "ili9325.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"


tact frq;

uint16_t mass [24] = {BLACK, BLUE, RED, GREEN, CYAN, MAGENTA, YELLOW, WHITE, GRAY, SKY, ORANGE, PINK, BROWN, VIOLET, SILVER, GOLD, BEGH, NAVY, DARK_GREEN, DARK_CYAN, MAROON, PURPLE, LIGHT_GREY, DARK_GREY};
//uint8_t font [8] = {0x0E,0x11,0x11,0x11,0x1F,0x11,0x11,0x00};
	
int main()
{
	ili9325 lcd;
	/*
	lcd.fill_screen(BLACK);
	lcd.draw (50,50,WHITE,BLACK, font);
	lcd.symbol (100,100, WHITE,BLACK,'7');
	lcd.string (150,300, WHITE,BLACK, "HELLO FROM STM32F030C8!!!");*/
  while (1)
  {
		for (uint8_t i=0;i<24;++i)
		{
			lcd.fill_screen(mass [i]);
			delay_ms (1000);
		}
  }
}
