#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"

#ifndef ILI9328_H
#define ILI9328_H

// ????????
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


class ili9328
{
public:
	Gpio pinData;
	Gpio pinCommand;
	enum commPins {CS=8, RS, WR, RD, RST};
	ili9328();
	void fill_screen (uint16_t color);
private:
	void init();
	void write_index (uint16_t index);
	void write_data (uint16_t data);	
	void write_reg (uint16_t _reg , uint16_t _data);	
	void point (uint16_t x, uint16_t y , uint16_t c);
  void set_cursor (uint16_t x , uint16_t y);
	void clear (uint16_t c);

	
};

#endif
