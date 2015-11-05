#include "mcp3551.h"

char number [10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char buff [4] = {0, 0, '.', '0'};

void mcp3551_init (void)
{
	init_spi_8 ();
	delay_ms (1);
}	

uint8_t mcp3551_Ready (void)
{
	CS_CLEAR;
	if (!(GPIOA->IDR & (1 << 6)))return 1;
	else
	{
		CS_SET;
		return 0;
	}
}

uint32_t getCode(void)
{
	uint8_t OVL,OVH;
	union 
	{
		uint32_t code32;
    uint8_t code8 [4];
	}byteCode;
	
	if (mcp3551_Ready())
	{
		byteCode.code8[3] = 0;
		byteCode.code8[2] = spi1_rx_8();
		byteCode.code8[1] = spi1_rx_8();
		byteCode.code8[0] = spi1_rx_8();
	}
	CS_SET;
	OVH = byteCode.code8[2]&(1 << 6);
	OVL = byteCode.code8[2]&(1 << 7);
	if (OVH && OVL) return 1;
	byteCode.code8[2] &= ~(1<<6|1<<7);
	return byteCode.code32;
}

double mcp3551_getTemp (uint32_t code)
{
	double RTD = (R_VAL*(double)code)/( 2097152.0 - (double)code);
  RTD = (RTD/PT) - 1;
    return (RTD * (255.8723 + RTD * (9.6 + RTD * 0.878)));
}

void mcp3551_buffer (double val)
{
	char dec, ones, decimal;
	dec = val/10;
	buff[0] = number [dec];
	ones = (int)val%10;
	buff[1] = number [ones];
	buff [2] = '.';
	decimal = (int)(val*10)%10;
	buff[3] = number [decimal];
}
