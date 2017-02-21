#include "stm32f0xx.h"   
#include "delay.h"
#include "spi.h"
#include "pin.h"
#include "dma.h"


#ifndef ILI9341_H
#define ILI9341_H


namespace ili9341Commands
{
	const uint8_t softwareReset = 0x01;
	const uint8_t powerControl1 = 0xC0;
	const uint8_t powerControl2 = 0xC1;
	const uint8_t vcomControl1  = 0xC5;
	const uint8_t vcomControl2  = 0xC7;
	const uint8_t frameControl  = 0xB1;
	const uint8_t memryAccessControl = 0x36;
	const uint8_t pixelFormatSet = 0x3A;
	const uint8_t displayFunctionControl = 0xB6;
	const uint8_t sleepOut      = 0x11;
	const uint8_t displayOn     = 0x29;
	const uint8_t coloumnAddressSet = 0x2A;
	const uint8_t pageAddressSet = 0x2B;
	const uint8_t memoryWrite   = 0x2C;

}


class Ili9341
{
//variables
public:
	struct sFont
	{
		const uint8_t * font;
		uint8_t width;
		uint8_t height;
		uint8_t shift;
	};
protected:
private:
	Spi * driver;
	Dma * dma;
	Pin dc, rst, cs;
//functions
public:
	Ili9341(Spi &, Gpio::Port po, uint8_t p, Gpio::Port rstpo, uint8_t rstpi);

	void setDma (Dma &);
	void pixel (uint16_t x , uint16_t y, const uint16_t color);
	void fillScreen (const uint16_t color);

	void symbol (uint16_t x, uint16_t y, const uint16_t color, const uint16_t fon, const uint8_t ch, sFont & s);
	//void symbol (uint16_t x, uint16_t y, const uint16_t color, const uint16_t fon, uint8_t ch, sFont & s);
	void string (uint16_t x, uint16_t y, const uint16_t color, const uint16_t fon, const char *str, sFont &f, uint8_t interval);
	void string (uint16_t x, uint16_t y, const uint16_t color, const uint16_t fon, const char *str, sFont &f, uint16_t n,uint8_t interval);
	void setCursor (uint16_t x , uint16_t y);
	void setCursor (uint16_t x1 , uint16_t y1, uint16_t x2, uint16_t y2);
	void drawArr (uint16_t x , uint16_t y, const uint16_t color, const uint16_t fon, const uint8_t *arr, uint16_t l, uint16_t width);
	void drawPic (uint16_t x , uint16_t y, const uint16_t *arr, uint16_t length, uint16_t width);
	void horLine (uint16_t x, uint16_t y, const uint16_t color, uint16_t length, uint8_t thick);
	void verLine (uint16_t x, uint16_t y, const uint16_t color, uint16_t length, uint8_t thick);
	void line (uint16_t x, uint16_t y, uint16_t color, uint16_t length, uint8_t thick);
	void rectangle (uint16_t x, uint16_t y, uint16_t color, uint16_t length, uint8_t width, uint8_t thick);
 void chipEnable ();
 void chipDisable ();
protected:
private:
	void data (uint8_t);
	void data16 (uint16_t);
	void dataDma (uint16_t * buf, uint32_t n);
	void command (uint8_t);
	void write (uint8_t);
	void init ();
	void setPage (uint16_t x1, uint16_t x2);
	void setColoumn (uint16_t y1, uint16_t y2);
	void setPosition (uint16_t x, uint16_t y);
	void pixel (const uint16_t color);

}; //ssd1289

#endif //__SSD1289_H__
