#include "ssd1289.h"

// default constructor
ssd1289::ssd1289()
:pinDataLow1 (Gpio::B) , pinDataLow2 (Gpio::B), pinDataHigh1 (Gpio::B) , pinDataHigh2 (Gpio::A),pinCommand1 (Gpio::A), pinCommand2 (Gpio::C)
{
	pinDataLow1.setOutPort(0x000F);
	pinDataLow1.setOutPort(0x00F0);
	pinDataHigh1.setOutPort(0x0F00);
	pinDataHigh2.setOutPort(0x0F00);
	pinCommand1.setOutPin (CS);
	pinCommand2.setOutPin (RS);
	pinCommand1.setOutPin (RST);
	pinCommand2.setOutPin (RD);
	pinCommand2.setOutPin (WR);
	pinCommand1.setPin(CS);
	pinCommand2.setPin(WR);
	init();
} //ssd1289

void ssd1289::point (uint16_t x , uint16_t y, uint16_t color)
{
	set_cursor(x,y);
	data (color);	
}

void ssd1289::fill_screen (uint16_t color)
{
	set_cursor(0,0);
	for (long i=0;i<76800;++i)data(color);
}

void ssd1289::set_cursor (uint16_t x , uint16_t y)
{
	wr_reg(0x004e, x);
    wr_reg(0x004f, y);
    index(0x0022);
}

void ssd1289::init()
{
	delay_ms(100);
	pinCommand1.setPin(RST);
	wr_reg(0X0007, 0X0021);   //далее записываем в регистры значения
	wr_reg(0X0000, 0X0001);
	wr_reg(0X0007, 0X0023);
	wr_reg(0X0010, 0X0000);
	delay_ms(30);
	wr_reg(0X0007, 0X0033);
	wr_reg(0X0011, 0X6838);
	wr_reg(0X0002, 0X0600);	
	/*
	
	
	wr_reg(0x00,0x0001);
	wr_reg(0x03,0xA8A4);
	wr_reg(0x0C,0x0000);
	wr_reg(0x0D,0x080C);
	wr_reg(0x0E,0x2B00);
	wr_reg(0x1E,0x00B7);
	wr_reg(0x01,0x2B3F);
	wr_reg(0x02,0x0600);
	wr_reg(0x10,0x0000);
	delay_ms(30);
	wr_reg(0x11,0x6070);
	wr_reg(0x05,0x0000);
	wr_reg(0x06,0x0000);
	wr_reg(0x16,0xEF1C);
	wr_reg(0x17,0x0003);
	wr_reg(0x07,0x0233);
	wr_reg(0x0B,0x0000);
	wr_reg(0x0F,0x0000);
	wr_reg(0x41,0x0000);
	wr_reg(0x42,0x0000);
	wr_reg(0x48,0x0000);
	wr_reg(0x49,0x013F);
	wr_reg(0x4A,0x0000);
	wr_reg(0x4B,0x0000);
	wr_reg(0x44,0xEF00);
	wr_reg(0x45,0x0000);
	wr_reg(0x46,0x013F);
	wr_reg(0x30,0x0707);
	wr_reg(0x31,0x0204);
	wr_reg(0x32,0x0204);
	wr_reg(0x33,0x0502);
	wr_reg(0x34,0x0507);
	wr_reg(0x35,0x0204);
	wr_reg(0x36,0x0204);
	wr_reg(0x37,0x0502);
	wr_reg(0x3A,0x0302);
	wr_reg(0x3B,0x0302);
	wr_reg(0x23,0x0000);
	wr_reg(0x24,0x0000);
	wr_reg(0x25,0x8000);
	wr_reg(0x4f,0x0000);
	wr_reg(0x4e,0x0000);
	index(0x22);*/
}

void ssd1289::index(uint16_t indx)
{
	pinCommand2.setPin(RD);	
	//отправляем команду
	pinCommand2.clearPin(RS);
	pinCommand1.clearPin(CS);
	pinDataLow1.setClearPort (0x000F);
	pinDataLow1.setClearPort (0x00F0);
	pinDataHigh1.setClearPort (0x0F00);
	pinDataHigh2.setClearPort (0x0F00);	
	pinDataLow1.setValPort(indx & 0x000F);
	pinDataLow2.setValPort(indx & 0x00F0);
	pinDataHigh1.setValPort (indx & 0x0F00);
	pinDataHigh2.setValPort ((indx & 0xF000)>>4);
	pinCommand2.clearPin(WR);
	delay_us(5);
	pinCommand2.setPin(WR);
	pinCommand1.setPin(CS);	
}

void ssd1289::data(uint16_t dta)
{
	pinCommand2.setPin(RD);
	//отправляем данные
	pinCommand2.setPin(RS);
	pinCommand1.clearPin(CS);
	pinDataLow1.setClearPort (0x000F);
	pinDataLow1.setClearPort (0x00F0);
	pinDataHigh1.setClearPort (0x0F00);
	pinDataHigh2.setClearPort (0x0F00);	
	pinDataLow1.setValPort(dta & 0x000F);
	pinDataLow2.setValPort(dta & 0x00F0);
	pinDataHigh1.setValPort (dta & 0x0F00);
	pinDataHigh2.setValPort ((dta & 0xF000)>>4);
	pinCommand2.clearPin(WR);
	delay_us(5);
	pinCommand2.setPin(WR);
	pinCommand1.setPin(CS);					
}

void ssd1289::wr_reg (uint16_t indx , uint16_t dta)
{
	pinCommand1.clearPin(CS);
	index (indx);
	data (dta);
	pinCommand1.setPin(CS);	
}

