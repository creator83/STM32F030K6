#include "stm32f0xx.h"                  // Device header
#include "delay.h"
#include "menu.h"


//Modify buffer function
//#define PPR_SOLDER

//Off digit
#define OFF 10

#define PORT GPIOA
#define DIGIT1 0 
#define DIGIT2 1
#define DIGIT3 2
#define DIGIT4 3

#ifndef SEGLED_H
#define SEGLED_H

void segled_init (void);

void Show_digit (uint8_t dig);

void segled_buffer (uint16_t val);

void led_number (void);

#endif
