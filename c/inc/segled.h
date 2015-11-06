#include "stm32f0xx.h"                  // Device header
#include "delay.h"

#define PORT GPIOA
#define DIGIT1 1 
#define DIGIT2 2
#define DIGIT3 3
#define DIGIT4 4

#ifndef SEGLED_H
#define SEGLED_H

void segled_init (void);

void Show_digit (uint8_t dig);

void buffer (uint16_t val);

uint16_t division (uint16_t n);


#endif
