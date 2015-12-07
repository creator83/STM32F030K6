#include "mcp3551.h"

#ifdef SOFTSPI



void mcp3551_init (void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	PORT->MODER &= ~(GPIO_MODER_MODER3|GPIO_MODER_MODER5|GPIO_MODER_MODER4);
	PORT->MODER |=GPIO_MODER_MODER3_0|GPIO_MODER_MODER5_0;
	PORT->ODR &= ~(1 << sck);
	CS_1;
	delay_ms (1);
}	

uint32_t spiread (void)
{
	int8_t i;
	uint32_t d=0;
	for (i=23;i>=0;i--)
	{
		PORT->ODR |= 1 << sck;
		delay_ms (1);
		if ((PORT->IDR & (1 << miso))) d|= (1 << i);
		PORT->ODR &=~ (1 << sck);
		delay_ms (1);
	}
	return d;
}

uint32_t getCode(void)
{
	uint8_t ovl,ovh;
	uint32_t bytecode;
	
	if (mcp3551_Ready())
	{
		bytecode = spiread();
	}
	CS_SET;
	ovh = bytecode&(1 << OVH);
	ovl = bytecode&(1 << OVL);
	if (ovl && ovh) return 1;
	
	//===from arduino===//
	/*
	if((ovh|ovl)))
	{
		bytecode &=~(1<<OVH);
		return bytecode;
	}
//check if sign bit is affected. if so, since it is two's compliment,
// substract it from 2^N
	else if(bytecode&(1<<21))
	{
		bytecode=0x400000-bytecode;
		return bytecode;
	}
	else return bytecode;*/
	//byteCode.code8[2] &= ~(1<<6|1<<7);
	return bytecode;
}

uint8_t mcp3551_Ready (void)
{
	CS_0;
	if (!(PORT->IDR & (1 << 6)))return 1;
	else
	{
		CS_1;
		return 0;
	}
}	

#else

void mcp3551_init (void)
{
	init_spi_8 ();
	delay_ms (1);
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

uint8_t mcp3551_Ready (void)
{
	CS_CLEAR;
	if (!(PORT->IDR & (1 << 6)))return 1;
	else
	{
		CS_SET;
		return 0;
	}
}	
	
#endif




/*
double mcp3551_getTemp (uint32_t code)
{
	double RTD = (R_VAL*(double)code)/( 2097152.0 - (double)code);
  RTD = (RTD/PT) - 1;
  return (RTD * (255.8723 + RTD * (9.6 + RTD * 0.878)));
}*/

uint16_t mcp3551_getTemp (uint32_t code)
{
	uint16_t temp;
	double t;
	double RTD = (R_VAL*(double)code)/( 2097152.0 - (double)code);
  RTD = (RTD/PT) - 1;
  t = (RTD * (255.8723 + RTD * (9.6 + RTD * 0.878)));
	temp = (uint16_t)t;
	return temp;
}
