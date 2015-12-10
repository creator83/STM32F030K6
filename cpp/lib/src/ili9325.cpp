#include "ili9325.h"

#ifdef BIT8
ili9325::ili9325()
:pinDataLow (Gpio::A), pinCommand (Gpio::A)
{
	pinDataLow.setOutPin(d0);
	pinDataLow.setOutPin(d1);
	pinDataLow.setOutPin(d2);
	pinDataLow.setOutPin(d3);
	pinDataLow.setOutPin(d4);
	pinDataLow.setOutPin(d5);
	pinDataLow.setOutPin(d6);
	pinDataLow.setOutPin(d7);
	pinCommand.setOutPin(CS);
	pinCommand.setOutPin(RS);
	pinCommand.setOutPin(RST);
	pinCommand.setOutPin(RD);
	pinCommand.setOutPin(WR);
	pinCommand.setPin (RST);
	pinCommand.setPin (CS);
	pinCommand.clearPin (RS);
	pinCommand.setPin (WR);	
	pinCommand.setPin (RD);
}
#else
ili9325::ili9325()
:pinDataLow (Gpio::B) , pinDataHigh (Gpio::D) , pinCommand (Gpio::C)
{
	pinDataLow.setDirPort(0xFF);
	pinDataHigh.setDirPort(0xFF);
	pinCommand.setDirPin(CS);
	pinCommand.setDirPin(RS);	
	pinCommand.setDirPin(RST);
	pinCommand.setDirPin(RD);	
	pinCommand.setDirPin(WR);
	pinCommand.setPin(RST);
	pinCommand.setPin(CS);
	pinCommand.clearPin(RS);
	pinCommand.setPin(WR);
	pinCommand.setPin(RD);
	init();
} //ili9325

#endif
void ili9325::init()
{
	pinCommand.clearPin(RST);
	delay_ms(100);
	pinCommand.setPin(RST);
	delay_ms(100);
	
	
	/*
	wr_reg(0x00E5,0x78F0);
	wr_reg(0x0001,0x0100);
	wr_reg(0x0002,0x0700);
	wr_reg(0x0003,0x1030);
	wr_reg(0x0004,0x0000);
	wr_reg(0x0008,0x0202);
	wr_reg(0x0009,0x0000);
	wr_reg(0x000A,0x0000);
	wr_reg(0x000C,0x0000);
	wr_reg(0x000D,0x0000);
	wr_reg(0x000F,0x0000);
	//power on sequence VGHVGL
	wr_reg(0x0010,0x0000);
	wr_reg(0x0011,0x0007);
	wr_reg(0x0012,0x0000);
	wr_reg(0x0013,0x0000);
	wr_reg(0x0007,0x0000);
	//vgh
	wr_reg(0x0010,0x1690);
	wr_reg(0x0011,0x0227);
	_delay_ms(100);
	//vregiout
	wr_reg(0x0012,0x009D); //0x001b
	_delay_ms(100);
	//vom amplitude
	wr_reg(0x0013,0x1900);
	_delay_ms(100);
	//vom H
	wr_reg(0x0029,0x0025);
	wr_reg(0x002B,0x000D);
	//gamma
	wr_reg(0x0030,0x0007);
	wr_reg(0x0031,0x0303);
	wr_reg(0x0032,0x0003);// 0006
	wr_reg(0x0035,0x0206);
	wr_reg(0x0036,0x0008);
	wr_reg(0x0037,0x0406);
	wr_reg(0x0038,0x0304);//0200
	wr_reg(0x0039,0x0007);
	wr_reg(0x003C,0x0602);// 0504
	wr_reg(0x003D,0x0008);
	//ram
	wr_reg(0x0050,0x0000);
	wr_reg(0x0051,0x00EF);
	wr_reg(0x0052,0x0000);
	wr_reg(0x0053,0x013F);
	wr_reg(0x0060,0xA700);
	wr_reg(0x0061,0x0001);
	wr_reg(0x006A,0x0000);
	wr_reg(0x0080,0x0000);
	wr_reg(0x0081,0x0000);
	wr_reg(0x0082,0x0000);
	wr_reg(0x0083,0x0000);
	wr_reg(0x0084,0x0000);
	wr_reg(0x0085,0x0000);
	wr_reg(0x0090,0x0010);
	wr_reg(0x0092,0x0600);
	wr_reg(0x0007,0x0133);
	wr_reg(0x00,0x0022);
	
	
	*/
	
	/************* Start Initial Sequence **********/

	wr_reg(0xE3, 0x3008); // Set internal timing
	wr_reg(0xE7, 0x0012); // Set internal timing
	wr_reg(0xEF, 0x1231); // Set internal timing
	wr_reg(0x01, 0x0100); // set SS and SM bit
	wr_reg(0x02, 0x0700); // set 1 line inversion
	wr_reg(0x03, 0x1020); // set GRAM write direction and BGR=1.
	wr_reg(0x04, 0x0000); // Resize register
	wr_reg(0x08, 0x0202); // set the back porch and front porch
	wr_reg(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]
	wr_reg(0x0A, 0x0000); // FMARK function
	wr_reg(0x0C, 0x0000); // RGB interface setting
	wr_reg(0x0D, 0x0000); // Frame marker Position
	wr_reg(0x0F, 0x0000); // RGB interface polarity

	/*************Power On sequence ****************/

	wr_reg(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	wr_reg(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	wr_reg(0x12, 0x0000); // VREG1OUT voltage
	wr_reg(0x13, 0x0000); // VDV[4:0] for VCOM amplitude
	delay_ms(200); // Dis-charge capacitor power voltage
	wr_reg(0x10, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
	wr_reg(0x11, 0x0227); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	delay_ms(50); // Delay 50ms
	wr_reg(0x12, 0x001C); // External reference voltage= Vci;
	delay_ms(50); // Delay 50ms
	wr_reg(0x13, 0x1800); // R13=1200 when R12=009D;VDV[4:0] for VCOM amplitude
	wr_reg(0x29, 0x001C); // R29=000C when R12=009D;VCM[5:0] for VCOMH
	wr_reg(0x2B, 0x000D); // Frame Rate = 91Hz
	delay_ms(50); // Delay 50ms
	wr_reg(0x20, 0x0000); // GRAM horizontal Address
	wr_reg(0x21, 0x0000); // GRAM Vertical Address

	/************Adjust the Gamma Curve************/

	wr_reg(0x30, 0x0007);
	wr_reg(0x31, 0x0302);
	wr_reg(0x32, 0x0105);
	wr_reg(0x35, 0x0206);
	wr_reg(0x36, 0x0808);
	wr_reg(0x37, 0x0206);
	wr_reg(0x38, 0x0504);
	wr_reg(0x39, 0x0007);
	wr_reg(0x3C, 0x0105);
	wr_reg(0x3D, 0x0808);

	/************Set GRAM area ************/

	wr_reg(0x50, 0x0000); // Horizontal GRAM Start Address
	wr_reg(0x51, 0x00EF); // Horizontal GRAM End Address
	wr_reg(0x52, 0x0000); // Vertical GRAM Start Address
	wr_reg(0x53, 0x013F); // Vertical GRAM Start Address
	wr_reg(0x60, 0xA700); // Gate Scan Line
	wr_reg(0x61, 0x0001); // NDL,VLE, REV
	wr_reg(0x6A, 0x0000); // set scrolling line

	/************ Partial Display Control ************/

	wr_reg(0x80, 0x0000);
	wr_reg(0x81, 0x0000);
	wr_reg(0x82, 0x0000);
	wr_reg(0x83, 0x0000);
	wr_reg(0x84, 0x0000);
	wr_reg(0x85, 0x0000);

	/************ Panel Control ************/

	wr_reg(0x90, 0x0010);
	wr_reg(0x92, 0x0000);
	wr_reg(0x93, 0x0003);
	wr_reg(0x95, 0x0110);
	wr_reg(0x97, 0x0000);
	wr_reg(0x98, 0x0000);
	wr_reg(0x07, 0x0133); // 262K color and display ON
	

}

void ili9325::index(uint8_t indx)
{
	//отправляем команду
	pinCommand.clearPin(RS);	
	pinCommand.clearPin(CS);
	pinDataLow.setValPort(0x00);
	pinCommand.clearPin(WR);
	//_delay_us(5);
	pinCommand.setPin(WR);	
	pinDataLow.setValPort(indx);
	pinCommand.clearPin(WR);
	//_delay_us(5);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}
void ili9325::data(uint16_t dta)
{
	//отправляем данные
	pinCommand.setPin(RS);
	pinCommand.clearPin(CS);
	pinDataLow.setValPort(dta>>8);
	pinCommand.clearPin(WR);
	//_delay_us(5);
	pinCommand.setPin(WR);
	pinDataLow.setValPort(dta);
	pinCommand.clearPin(WR);
	//_delay_us(5);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
	
}

void ili9325::wr_reg (unsigned char indx , unsigned int dta)
{
	index (indx);
	data (dta);
}
/*
void ili9325::wr_reg (unsigned char indx , unsigned int dta)
{
	pinCommand.clearPin(CS);
	
	pinDataLow.setValPort(0x00);
	pinCommand.clearPin(WR);
	_delay_us(5);
	pinCommand.setPin(WR);	
	pinDataLow.setValPort(indx);	
	pinCommand.clearPin(WR);
	_delay_us(5);
	pinCommand.setPin(WR);
	pinCommand.setPin(RS);
	pinDataLow.setValPort(dta>>8);
	pinCommand.clearPin(WR);
	_delay_us(5);
	pinCommand.setPin(WR);	
	pinDataLow.setValPort(dta);	
	pinCommand.clearPin(WR);
	_delay_us(5);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}*/
void ili9325::set_cursor (uint16_t x , uint16_t y)
{
	wr_reg (0x20 , x);
	wr_reg(0x21 , y);
	index(0x0022);
}

void ili9325::point (uint16_t x , uint16_t y, uint16_t color)
{
	set_cursor(x,y);
	data(color);
}

void ili9325::fill_screen (uint16_t color)
{
	set_cursor(0,0);
	for (long i=0;i<76800;++i)
	{
		data(color);
	}
}

void ili9325::set_area (uint16_t x1 , uint16_t y1 , uint16_t x2 , uint16_t y2)
{
	x_start = x1;
	x_end = x2;
	y_start = y1;
	y_end = y2;
	wr_reg(h_Gram_start,x1);
	wr_reg(v_Gram_start,y1);
	wr_reg(h_Gram_end,x2);
	wr_reg(v_Gram_end,y2);
}

void ili9325::putchar (uint16_t x , uint16_t y , char * ch , uint16_t color , uint16_t background)
{
	set_cursor(x,y);
	
}


