#include "stm32f0xx.h"                  // Device header
#include "delay.h"  
#include "spi.h"

#define R_VAL 13407
#define PT 100
#define SOFTSPI
#define PORT GPIOA
#define cs 4
#define sck 5
#define miso 6
#define CS_0 PORT->ODR &= ~ (1 << cs)
#define CS_1 PORT->ODR |=1<<cs
#define OVH 22
#define OVL 23

#ifndef MCP3551_H
#define MCP3551_H

void mcp3551_init (void);

#ifdef SOFTSPI
uint32_t spiread (void);
#endif

uint8_t mcp3551_Ready (void);

uint32_t getCode(void);

uint16_t mcp3551_getTemp (uint32_t code);


#endif
