#include "stm32f0xx.h"                  // Device header
#include "encoder.h"  
#include "max6675.h"

#ifndef MENU_H
#define MENU_H

void button_enc_init (void);

void tim14_init(void);

void blinking_menu (void);

#endif
