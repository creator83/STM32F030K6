#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "font.h"

#ifndef SSD1289_H
#define SSD1289_H


const uint16_t BLACK =	0x0000;
const uint16_t BLUE	 =  0xF800;
const uint16_t RED 	 =  0x001F;
const uint16_t GREEN =	0x07E0;
const uint16_t CYAN	 =  0x07FF;
const uint16_t MAGENTA =0xF81F;
const uint16_t YELLOW =	0xFFE0;
const uint16_t WHITE =	0xFFFF;

const uint16_t GRAY	   =	 0xE79C;
const uint16_t SKY     =	 0x5d1C;
const uint16_t ORANGE  =   0xFCA0;
const uint16_t PINK    =	 0xF97F;
const uint16_t BROWN   =	 0x8200;
const uint16_t VIOLET  =	 0x9199;
const uint16_t SILVER  =   0xA510;
const uint16_t GOLD    =	 0xA508;
const uint16_t BEGH    =	 0xF77B;
const uint16_t NAVY    =	 0x000F;
const uint16_t DARK_GREEN =0x03E0;
const uint16_t DARK_CYAN  =0x03EF;
const uint16_t MAROON     =0x7800;
const uint16_t PURPLE     =0x7BE0;
const uint16_t LIGHT_GREY =0xC618;
const uint16_t DARK_GREY  =0x7BEF;

class ssd1289
{
//variables
public:
protected:
private:
	Gpio pinDataLow1;
	Gpio pinDataLow2;
	Gpio pinDataHigh1;
	Gpio pinDataHigh2;
	Gpio pinCommand1;
	Gpio pinCommand2;
	enum commPins1 {RST=12, CS=15};
	enum commPins2 { RS=13, WR ,RD};

//functions
public:
	ssd1289();
	void point (uint16_t x , uint16_t y, uint16_t color);
	void fill_screen (uint16_t color);
	void symbol (uint16_t x, uint16_t y, uint16_t color, uint16_t phone, uint8_t ch);
	void string (uint16_t x, uint16_t y, uint16_t color, uint16_t phone, char *str);
	void set_cursor (uint16_t x , uint16_t y);
	void draw (uint16_t x , uint16_t y, uint16_t color, uint16_t phone, uint8_t *ch);
protected:
private:
	void init();
	void index(uint16_t indx);
	void data(uint16_t dta);
	void wr_reg (uint16_t indx , uint16_t dta);

}; //ssd1289

#endif //__SSD1289_H__
