#include "stm32f0xx.h"                  // Device header
#include "delay.h"  
#include "spi.h"

#define R_VAL 13407
#define PT 100

#ifndef MCP3551_H
#define MCP3551_H

void mcp3551_init (void);

uint8_t mcp3551_Ready (void);

uint32_t getCode(void);

uint16_t mcp3551_getTemp (uint32_t code);


#endif
