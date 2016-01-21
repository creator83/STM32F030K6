#include "stm32f0xx.h"                  // Device header
#include "tact.h"
#include "Gpio.h"
#include "delay.h"

#ifndef ILI9325_H
#define ILI9325_H

//#define BIT8

#define 		TS_SIZE_X						240
#define 		TS_SIZE_Y		        		320
#define 		TS_VAL_ENTRY_MOD				0x0030
#define 		TS_INS_START_OSC                0x00 //data read at this instruction should be 0x0789 --> use for test connection
#define 		TS_INS_DRIV_OUT_CTRL            0x01
#define 		TS_INS_DRIV_WAV_CTRL            0x02
#define 		TS_INS_ENTRY_MOD                0x03
#define 		TS_INS_RESIZE_CTRL              0x04
#define 		TS_INS_DISP_CTRL1               0x07
#define 		TS_INS_DISP_CTRL2               0x08
#define 		TS_INS_DISP_CTRL3               0x09
#define 		TS_INS_DISP_CTRL4               0x0A
#define 		TS_INS_RGB_DISP_IF_CTRL1        0x0C
#define 		TS_INS_FRM_MARKER_POS           0x0D
#define 		TS_INS_RGB_DISP_IF_CTRL2        0x0F
#define 		TS_INS_POW_CTRL1                0x10
#define 		TS_INS_POW_CTRL2                0x11
#define 		TS_INS_POW_CTRL3                0x12
#define 		TS_INS_POW_CTRL4                0x13
#define 		TS_INS_GRAM_HOR_AD              0x20
#define 		TS_INS_GRAM_VER_AD              0x21
#define 		TS_INS_RW_GRAM                  0x22
#define 		TS_INS_POW_CTRL7                0x29
#define 		TS_INS_FRM_RATE_COL_CTRL        0x2B
#define 		TS_INS_GAMMA_CTRL1              0x30
#define 		TS_INS_GAMMA_CTRL2              0x31
#define 		TS_INS_GAMMA_CTRL3              0x32
#define 		TS_INS_GAMMA_CTRL4              0x35
#define 		TS_INS_GAMMA_CTRL5              0x36
#define 		TS_INS_GAMMA_CTRL6              0x37
#define 		TS_INS_GAMMA_CTRL7              0x38
#define 		TS_INS_GAMMA_CTRL8              0x39
#define 		TS_INS_GAMMA_CTRL9              0x3C
#define 		TS_INS_GAMMA_CTRL10             0x3D
#define 		TS_INS_HOR_START_AD             0x50
#define 		TS_INS_HOR_END_AD               0x51
#define 		TS_INS_VER_START_AD             0x52
#define 		TS_INS_VER_END_AD               0x53
#define 		TS_INS_GATE_SCAN_CTRL1          0x60
#define 		TS_INS_GATE_SCAN_CTRL2          0x61
#define 		TS_INS_GATE_SCAN_CTRL3          0x6A
#define 		TS_INS_PART_IMG1_DISP_POS       0x80
#define 		TS_INS_PART_IMG1_START_AD       0x81
#define 		TS_INS_PART_IMG1_END_AD         0x82
#define 		TS_INS_PART_IMG2_DISP_POS       0x83
#define 		TS_INS_PART_IMG2_START_AD       0x84
#define 		TS_INS_PART_IMG2_END_AD         0x85
#define 		TS_INS_PANEL_IF_CTRL1           0x90
#define 		TS_INS_PANEL_IF_CTRL2           0x92
#define 		TS_INS_PANEL_IF_CTRL3           0x93
#define 		TS_INS_PANEL_IF_CTRL4           0x95
#define 		TS_INS_PANEL_IF_CTRL5           0x97
#define 		TS_INS_PANEL_IF_CTRL6           0x98

//registers

const uint16_t DRIVER_OUTPUT_CONTROL_1 = 0x01;
const uint16_t LCD_DRIVING_CONTROL     = 0x02;
const uint16_t ENTRY_MODE         		 = 0x03;
const uint16_t RESIZE_CONTROL          = 0x04;
const uint16_t DISPLAY_CONTROL_1       = 0x07;
const uint16_t DISPLAY_CONTROL_2       = 0x08;
const uint16_t DISPLAY_CONTROL_3       = 0x09;
const uint16_t DISPLAY_CONTROL_4       = 0x0A;
const uint16_t RGB_DISPLAY_INTERFACE_CONTROL_1 = 0x0C;
const uint16_t FRAME_MARKER_POSITION   = 0x0D;
const uint16_t RGB_DISPLAY_INTERFACE_CONTROL_2 = 0x0F;
const uint16_t POWER_CONTROL_1         = 0x10;
const uint16_t POWER_CONTROL_2         = 0x11;
const uint16_t POWER_CONTROL_3         = 0x12;
const uint16_t POWER_CONTROL_4         = 0x13;
const uint16_t POWER_CONTROL_7         = 0x29;
const uint16_t FRAME_RATE_COLOR_CONTROL= 0x2B;
const uint16_t HORIZONTAL_ADDRESS_SET  = 0x20;
const uint16_t VERTICAL_ADDRESS_SET    = 0x21;
const uint16_t GAMMA_CONTROL_1         = 0x30;
const uint16_t GAMMA_CONTROL_2         = 0x31;
const uint16_t GAMMA_CONTROL_3         = 0x32;
const uint16_t GAMMA_CONTROL_4         = 0x35;
const uint16_t GAMMA_CONTROL_5         = 0x36;
const uint16_t GAMMA_CONTROL_6         = 0x37;
const uint16_t GAMMA_CONTROL_7         = 0x38;
const uint16_t GAMMA_CONTROL_8         = 0x39;
const uint16_t GAMMA_CONTROL_9         = 0x3C;
const uint16_t GAMMA_CONTROL_10        = 0x3D;
const uint16_t WINDOW_HORIZONTAL_ADDRESS_START = 0x50;
const uint16_t WINDOW_HORIZONTAL_ADDRESS_END   = 0x51;
const uint16_t WINDOW_VERTICAL_ADDRESS_START   = 0x52;
const uint16_t WINDOW_VERTICAL_ADDRESS_END     = 0x53;
const uint16_t GATE_SCAN_CONTROL_1     = 0x60;
const uint16_t GATE_SCAN_CONTROL_2     = 0x61;
const uint16_t GATE_SCAN_CONTROL_3     = 0x6A;
const uint16_t PARTIAL_IMAGE_1_DISPLAY_POSITION       = 0x80;
const uint16_t PARTIAL_IMAGE_1_RAM_START_LINE_ADDRESS = 0x81;
const uint16_t PARTIAL_IMAGE_1_RAM_END_LINE_ADDRESS   = 0x82;
const uint16_t PARTIAL_IMAGE_2_DISPLAY_POSITION       = 0x83;
const uint16_t PARTIAL_IMAGE_2_RAM_START_LINE_ADDRESS = 0x84;
const uint16_t PARTIAL_IMAGE_2_RAM_END_LINE_ADDRESS   = 0x85;
const uint16_t PANEL_INTERFACE_CONTROL_1              = 0x90;
const uint16_t PANEL_INTERFACE_CONTROL_2              = 0x92;
const uint16_t PANEL_INTERFACE_CONTROL_4              = 0x95;

//colors

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
	
protected:
private:
	enum commPins1 {RST=12, CS=15};
	enum commPins2 { RS=13, WR ,RD};

#ifdef BIT8
	Gpio pinDataLow;
	enum dataPins {d0,d1,d2,d3,d4,d5,d6,d7};
#else
	Gpio pinDataLow1;
	Gpio pinDataLow2;
	Gpio pinDataHigh1;
	Gpio pinDataHigh2;
	Gpio pinCommand1;
	Gpio pinCommand2;
#endif
	
	uint16_t x_start, x_end, y_start, y_end;

//functions
public:
	ili9325();
	void point (uint16_t x , uint16_t y, uint16_t color);
	void fill_screen (uint16_t color);
	void set_area (uint16_t x1, uint16_t y1, uint16_t x2 , uint16_t y2);
	void set_cursor (uint16_t x , uint16_t y);
	void data (uint16_t dta);	
	void putchar (uint16_t x , uint16_t y , char * ch , uint16_t color , uint16_t background);

protected:
private:
	void init();
	void index(uint16_t indx);

	//void wr_reg (unsigned int indx , unsigned int dta);
	void wr_reg (uint16_t indx , uint16_t dta);	

}; //ili9325

#endif //__ILI9325_H__
