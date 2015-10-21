#include "delay.h"

uint16_t delay;

void SysTick_Handler (void)
{
	if (delay > 0)delay--;
}

void delay_ms (uint16_t del)
{
	SysTick_Config (SystemCoreClock/1000);
	delay = del;
	while (delay);
}

void delay_us (uint16_t del)
{
	SysTick_Config (SystemCoreClock/1000000);
	delay = del;
	while (delay);
}
