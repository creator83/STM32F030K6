#include "stm32f0xx.h"                  // Device header
#include "gpio.h"
#include "Spi.h"
#include "delay.h"
#include "dma.h"
#include "font6x8.h"


namespace Pcd8544Def
{
//===Defenitions===//
//CS
const Gpio::Port CsPort = Gpio::A;
const uint8_t CsPin = 1;

//SCK
const Gpio::Port SckPort = Gpio::A;
const uint8_t SckPin = 5;

//MOSI
const Gpio::Port MosiPort = Gpio::A;
const uint8_t MosiPin = 7;
	
//RESET
const Gpio::Port RstPort = Gpio::A;
const uint8_t RstPin = 3;	
	
//DC
const Gpio::Port DcPort = Gpio::A;
const uint8_t DcPin = 2;
}

#ifndef PCD8544_H
#define PCD8544_H

//basic command
#define lcd_setfunction    0x20
#define lcd_displayblank   0x08 
#define lcd_displaynormal  0x0C
#define lcd_displayflash   0x09 
#define lcd_displayinverse 0x0D
#define lcd_setYaddr       0x40 
#define lcd_setXaddr       0x80

//??????????? ???????
#define lcd_setfunctionext 0x21
#define lcd_tempcoef       0x04
#define lcd_setbias        0x10
#define lcd_setvop         0x80

//????????????? ???????????
#define temp0              0
#define temp1              1
#define temp2              2
#define temp3              3

//bias
#define bias_1_100         0
#define bias_1_80          1
#define bias_1_65          2
#define bias_1_48          3
#define bias_1_40          4
#define bias_1_24          5
#define bias_1_18          6
#define bias_1_10          7

//

const char width = 84;
const char height= 48;
const char page  =  6;
const uint16_t bufferSize = page*width;

class Pcd8544
{
public:
	struct sFont
	{
		const uint8_t * font;
		uint8_t width;
		uint8_t shift;
	};		
	enum dmaMode {off, on};
	//variable
private:
	static uint8_t screenBuffer [page][width];
	Spi* spimodule;
	Gpio reset, dc;
	Dma mem2spi1;
	Dma mem2buff;
	static char Big_number[10][42]; 
	static char Med_number1[10][18]; 
	static const char null_val;
	static dmaMode dmaMode_;
public:
	Pcd8544 (Spi &);
	void init ();
	void dma (dmaMode );
	void dmaSetting ();
	void command (uint8_t comm);
	void data (uint8_t dta, uint16_t n);
	void array (const uint8_t *dta, uint16_t n);
	void byte (uint8_t dta);
	void setPosition (uint8_t x, uint8_t y);
	void setLinePosition (uint8_t line, uint8_t position);

	void clearScreen ();
	void clearScreen (uint8_t x,uint8_t y,uint8_t dx,uint8_t dy);
	void fillScreen ();
	void chipAssert ();
	void chipDisassert ();
  void character (const char ch, sFont & s);
	void character (uint8_t line , uint8_t position , const char ch, sFont &);
	void string (uint8_t line , uint8_t position, const char *str, sFont &, uint8_t interval=0);

	void parsingBin (uint8_t line , uint8_t position, uint8_t interval, uint8_t number, sFont &);
	
	
	void characterToBuffer (uint8_t line , uint8_t position , const char ch, sFont &);
	void characterToBufferDma (uint8_t line , uint8_t position , const char ch, sFont &);
	void stringToBuffer (uint8_t line , uint8_t position, const char *str, sFont &, uint8_t interval=0);
	void stringToBufferDma (uint8_t line , uint8_t position, const char *str, sFont &, uint8_t interval=0);
	void drawBuffer ();
	void drawBuffer (uint8_t line, uint8_t x1, uint8_t x2);
	void drawBufferDma ();
	void drawBufferDma (uint8_t line, uint8_t x1, uint8_t x2);
	void drawDma ();
	void draw_font(char * font, char ch);
	void draw_big_number(uint8_t x, uint8_t y, uint8_t ch);
	void draw_char(uint8_t x , uint8_t y , char ch);
	void draw_char_buffer (uint8_t x , uint8_t y , char ch);
	void draw_char(char ch);
	void draw_picture (const char * pic, uint16_t l);
	void pixel (uint8_t x , uint8_t y);
	void hor_line (uint8_t x1 , uint8_t x2,  uint8_t y, uint8_t thick);
	void ver_line (uint8_t x , uint8_t y1,  uint8_t y2, uint8_t thick);
	void string_screen (uint8_t x , uint8_t y , char *str);
	void bin_number (uint8_t x , uint8_t y , uint8_t num);

	bool spi_bsy ();
	//function with buffer
	void draw_buffer ();
	void string_buffer (uint8_t x , uint8_t y , char *str);
	void hor_line_buffer (uint8_t x1 , uint8_t x2,  uint8_t y1, uint8_t thick);
	void ver_line_buffer (uint8_t x , uint8_t y1,  uint8_t y2, uint8_t thick);
	
	void clear_buffer ();
	void clear_buffer (uint8_t x,uint8_t y,uint8_t dx,uint8_t dy);
	void refresh_buffer ();
	void point_buffer (uint8_t x, uint8_t y, uint8_t thick);
	void draw_font_buffer(uint8_t * font, char ch);
	void big_number_buffer (uint8_t x , uint8_t y , uint8_t num);
	void med_number_buffer (uint8_t x , uint8_t y , uint8_t num);
	void string_number_buffer (uint8_t x , uint8_t y , uint8_t *arr, uint8_t l);
	void string_numberM_buffer (uint8_t x , uint8_t y , uint8_t *arr, uint8_t l);
	uint32_t * buffer_adress ();
	
};




#endif
