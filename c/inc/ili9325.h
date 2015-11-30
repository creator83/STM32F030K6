#include "stm32f0xx.h"                  // Device header
#include "delay.h"  

#define CS 8
#define RS 9
#define WR 10
#define RD 11
#define RESET 12



#define X_rezolution 240
#define Y_rezolution 320

#define BLACK   	 0x0000
#define BLUE	   	 0x001F
#define RED 	   	 0xF800
#define GREEN   	 0x07E0
#define CYAN	  	 0x07FF
#define MAGENTA 	 0xF81F
#define YELLOW  	 0xFFE0
#define WHITE   	 0xFFFF
#define GRAY	  	 0xE79C

#define SKY     	 0x5d1C
#define ORANGE     0xFCA0
#define PINK    	 0xF97F
#define BROWN   	 0x8200
#define VIOLET  	 0x9199
#define SILVER     0xA510
#define GOLD    	 0xA508
#define BEGH    	 0xF77B
#define NAVY    	 0x000F
#define DARK_GREEN 0x03E0
#define DARK_CYAN  0x03EF
#define MAROON     0x7800
#define PURPLE     0x7BE0
#define LIGHT_GREY 0xC618
#define DARK_GREY  0x7BEF




#ifndef ILI9325_H
#define ILI9325_H

void ili9325_init (void);
void ili9325_index (uint8_t indx);
void ili9325_data (uint16_t data);
void ili9325_wr_reg (uint8_t indx, uint16_t data);
void ili9325_set_cursor (uint16_t x , uint16_t y);
void ili9325_point (uint16_t x , uint16_t y, uint16_t color);
void ili9325_fill_screen (uint16_t color);


#endif
