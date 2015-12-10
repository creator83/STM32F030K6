#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "Gpio.h"
#include "Spi.h"
#include "delay.h"

#ifndef MCP3551_H
#define MCP3551_H

	const uint8_t pt = 100;
	const uint16_t r_val = 13407;
	
	const int8_t CS = 4;// pin CS


class mcp3551
{
//variables
public:
	int32_t byteCode;

protected:
private:
	//Gpio pin;
	bool OVH, OVL;
	spi spi1;
	union {
	int32_t ByteCode;
	uint8_t Byte[4];
	}spi_code ;

	
//functions
public:
	mcp3551();
	float getTemp ();
	bool getCode();
	
	
protected:
private:

	bool getOVH();
	bool getOVL();
	bool isReady();

}; //mcp3551

#endif //__MCP3551_H__
