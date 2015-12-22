#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"

#ifndef SSD1289_H
#define SSD1289_H


const uint16_t BLACK =	0x0000;
const uint16_t BLUE	 =  0xF800;
const uint16_t RED 	 =  0x001F;
const uint16_t GREEN =	0x07E0;
const uint16_t CYAN	 =  0x07FF;
const uint16_t MAGENTA= 0xF81F;
const uint16_t YELLOW=	0xFFE0;
const uint16_t WHITE=	0xFFFF;

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
	void set_cursor (uint16_t x , uint16_t y);
protected:
private:
	void init();
	void index(uint16_t indx);
	void data(uint16_t dta);
	void wr_reg (uint16_t indx , uint16_t dta);

}; //ssd1289

#endif //__SSD1289_H__
