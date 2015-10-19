#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "Gpio.h"

#ifndef __ILI9325_H__
#define __ILI9325_H__

#define BIT8


const unsigned int BLACK   =	 0x0000;
const unsigned int BLUE	   =	 0x001F;
const unsigned int RED 	   =	 0xF800;
const unsigned int GREEN   =	 0x07E0;
const unsigned int CYAN	   =	 0x07FF;
const unsigned int MAGENTA =	 0xF81F;
const unsigned int YELLOW  =	 0xFFE0;
const unsigned int WHITE   =	 0xFFFF;

const unsigned int GRAY	   =	 0xE79C;
const unsigned int SKY     =	 0x5d1C;
const unsigned int ORANGE  =     0xFCA0;
const unsigned int PINK    =	 0xF97F;
const unsigned int BROWN   =	 0x8200;
const unsigned int VIOLET  =	 0x9199;
const unsigned int SILVER  =     0xA510;
const unsigned int GOLD    =	 0xA508;
const unsigned int BEGH    =	 0xF77B;
const unsigned int NAVY    =	 0x000F;
const unsigned int DARK_GREEN =  0x03E0;
const unsigned int DARK_CYAN  =	 0x03EF;
const unsigned int MAROON     =  0x7800;
const unsigned int PURPLE     =	 0x7BE0;
const unsigned int LIGHT_GREY =	 0xC618;
const unsigned int DARK_GREY  =  0x7BEF;


/*
************registers****************
*/


//GRAM area
const unsigned char h_Gram_start = 0x50;
const unsigned char h_Gram_end   = 0x51;
const unsigned char v_Gram_start = 0x52;
const unsigned char v_Gram_end   = 0x53;

//Entry mode
const unsigned char entry_mode = 0x03;

//Resize
const unsigned char resize = 0x04;


class ili9325
{
//variables
public:
	enum commPins {RST, WR , CS , RS ,RD};
protected:
private:
	Gpio pinDataLow;
	Gpio pinDataHigh;
	Gpio pinCommand;
	unsigned int x_start, x_end, y_start, y_end;

//functions
public:
	ili9325();
	void point (char x , char y, unsigned int color);
	void fill_screen (unsigned int color);
	void set_area (unsigned int x1 , unsigned int y1 , unsigned int x2 , unsigned int y2);
	void set_cursor (char x , char y);
	void data(unsigned int dta);	
	void putchar (unsigned int x , unsigned int y , char * ch , unsigned int color , unsigned int background);

protected:
private:
	void init();
	void index(unsigned char indx);

	//void wr_reg (unsigned int indx , unsigned int dta);
	void wr_reg (unsigned char indx , unsigned int dta);	

}; //ili9325

#endif //__ILI9325_H__
