#include "stm32f0xx.h"                  // Device header
#include "delay.h"


#define trig 1
#define echo 0


#ifndef HCSR4_H
#define HCSR4_H

void HC_SRC4_Init(void);
void HC_SRC4_Send_strob(void);
void init_interp (void);
void init_timer (void);
void timer_Start_Stop (char flag);
double HC_SRC4_Convert_CM (uint16_t N_t);
void HC_SRC4_to_buff (double);

#endif

