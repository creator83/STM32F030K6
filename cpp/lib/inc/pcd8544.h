#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"
#include "Spi.h"
#include "delay.h"
//#include "font6x8.h"

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

class pcd8544
{
	//variable
	spi spi1;
	Gpio pin;
	enum PIN {RST=1, DC=7};
	enum COM {COMMAND, DATA};
	static uint8_t buffer [width*page];
	static char NewFontLAT[]; 
	static char Big_number[]; 
public:
	pcd8544();
	void send_byte (uint8_t dta , bool com_);
	void send_byte (uint8_t dta);
	void send_data (uint8_t *dta);
	void send_comm (uint8_t comm);
	void clear_screen ();

	void fill_screen ();
	void clear_buffer ();
	void refresh_buffer ();
	void init ();
	void gotoxy(uint8_t x, uint8_t y);
	void draw_font(char * font, char ch);
	void draw_font_buffer(uint8_t * font, char ch);
	void draw_big_number(uint8_t x, uint8_t y, uint8_t ch);
	void draw_char(uint8_t x , uint8_t y , char ch);
	void draw_char_buffer (uint8_t x , uint8_t y , char ch);
	void draw_char(char ch);
	void draw_buffer ();
	void draw_pictur (const char * pic, uint16_t l);
	void pixel (uint8_t x , uint8_t y);
	void hor_line_buffer (uint8_t x1 , uint8_t x2,  uint8_t y1, uint8_t thick);
	void string_screen (uint8_t x , uint8_t y , char *str);
	void string_buffer (uint8_t x , uint8_t y , char *str);
	void bin_number (uint8_t x , uint8_t y , uint8_t num);
	void assert_chip ();
	void desassert_chip ();
	bool spi_bsy ();

};

inline void pcd8544::desassert_chip (){spi1.Set_CS ();}
inline bool  pcd8544::spi_bsy (){return spi1.flag_bsy();}



#endif
