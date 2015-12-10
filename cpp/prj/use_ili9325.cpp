#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "ili9325.h"

  tact frq;
	
int main()
{
	ili9325 lcd;
  lcd.fill_screen (YELLOW);
  while (1)
  {
  }
  
}
