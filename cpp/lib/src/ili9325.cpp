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
	pinCommand2.setPin(RD);
	init();
} 

#endif
void ili9325::init()
{
	pinCommand1.clearPin(RST);
	delay_ms(100);
	pinCommand1.setPin(RST);
	delay_ms(100);
	
wr_reg(0x00E3,0x3008);                          //set the internal timing
wr_reg(0x00E7,0x0012);                          //set the internal timing
wr_reg(0x00EF,0x1231);                          //set the internal timing
wr_reg(TS_INS_START_OSC,0x0001);                //start oscillator
delay_ms(50);
wr_reg(TS_INS_DRIV_OUT_CTRL,0x0100);            //set SS, SM
wr_reg(TS_INS_DRIV_WAV_CTRL,0x0700);            //set 1 line inversion
wr_reg(TS_INS_ENTRY_MOD,TS_VAL_ENTRY_MOD);      //set GRAM write direction, BGR=0
wr_reg(TS_INS_RESIZE_CTRL,0x0000);              //no resizing
wr_reg(TS_INS_DISP_CTRL2,0x0202);               //front & back porch periods = 2
wr_reg(TS_INS_DISP_CTRL3,0x0000);
wr_reg(TS_INS_DISP_CTRL4,0x0000);
//
 wr_reg(TS_INS_RGB_DISP_IF_CTRL1,0x0000);
wr_reg(TS_INS_FRM_MARKER_POS,0x0000);
wr_reg(TS_INS_RGB_DISP_IF_CTRL2,0x0000);
wr_reg(TS_INS_POW_CTRL1,0x0000);
wr_reg(TS_INS_POW_CTRL2,0x0007);
wr_reg(TS_INS_POW_CTRL3,0x0000);
wr_reg(TS_INS_POW_CTRL4,0x0000);
delay_ms(200);
wr_reg(TS_INS_POW_CTRL1,0x1690);
wr_reg(TS_INS_POW_CTRL2,0x0227); //(0x0137);
delay_ms(50);
wr_reg(TS_INS_POW_CTRL3,0x001A); //(0x013C);
delay_ms(50);
wr_reg(TS_INS_POW_CTRL4,0x1800); //(0x1400);
wr_reg(TS_INS_POW_CTRL7,0x002A); //(0x0007);
delay_ms(50);
wr_reg(TS_INS_GRAM_HOR_AD,0x0000);
wr_reg(TS_INS_GRAM_VER_AD,0x0000);
wr_reg(TS_INS_GAMMA_CTRL1,0x0007);
wr_reg(TS_INS_GAMMA_CTRL2,0x0605);
wr_reg(TS_INS_GAMMA_CTRL3,0x0106);
wr_reg(TS_INS_GAMMA_CTRL4,0x0206);
wr_reg(TS_INS_GAMMA_CTRL5,0x0808);
wr_reg(TS_INS_GAMMA_CTRL6,0x0007);
wr_reg(TS_INS_GAMMA_CTRL7,0x0201);
wr_reg(TS_INS_GAMMA_CTRL8,0x0007);
wr_reg(TS_INS_GAMMA_CTRL9,0x0602);
wr_reg(TS_INS_GAMMA_CTRL10,0x0808);
wr_reg(TS_INS_HOR_START_AD,0x0000);
wr_reg(TS_INS_HOR_END_AD,0x00EF);
wr_reg(TS_INS_VER_START_AD,0x0000);
wr_reg(TS_INS_VER_END_AD,0x013F);
wr_reg(TS_INS_GATE_SCAN_CTRL1,0xA700);
wr_reg(TS_INS_GATE_SCAN_CTRL2,0x0001);
wr_reg(TS_INS_GATE_SCAN_CTRL3,0x0000);
wr_reg(TS_INS_PART_IMG1_DISP_POS,0x0000);
wr_reg(TS_INS_PART_IMG1_START_AD,0x0000);
wr_reg(TS_INS_PART_IMG1_END_AD,0x0000);
wr_reg(TS_INS_PART_IMG2_DISP_POS,0x0000);
wr_reg(TS_INS_PART_IMG2_START_AD,0x0000);
wr_reg(TS_INS_PART_IMG2_END_AD,0x0000);
wr_reg(TS_INS_PANEL_IF_CTRL1,0x0010);
wr_reg(TS_INS_PANEL_IF_CTRL2,0x0000);
wr_reg(TS_INS_PANEL_IF_CTRL3,0x0003);
wr_reg(TS_INS_PANEL_IF_CTRL4,0x0110);
wr_reg(TS_INS_PANEL_IF_CTRL5,0x0000);
wr_reg(TS_INS_PANEL_IF_CTRL6,0x0000);
wr_reg(TS_INS_DISP_CTRL1,0x0133);
	
	
	/*	
	wr_reg(0xE5, 0x78F0); // set SRAM internal timing
	wr_reg(0x01, 0x0100); // set Driver Output Control  
	wr_reg(0x02, 0x0700); // set 1 line inversion  
	wr_reg(0x03, 0x1030); // set GRAM write direction and BGR=1.  
	wr_reg(0x04, 0x0000); // Resize register  
	wr_reg(0x08, 0x0207); // set the back porch and front porch  
	wr_reg(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]  
	wr_reg(0x0A, 0x0000); // FMARK function  
	wr_reg(0x0C, 0x0000); // RGB interface setting  
	wr_reg(0x0D, 0x0000); // Frame marker Position  
	wr_reg(0x0F, 0x0000); // RGB interface polarity  
	//===Power On sequence ===//  
	wr_reg(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB  
	wr_reg(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]  
	wr_reg(0x12, 0x0000); // VREG1OUT voltage  
	wr_reg(0x13, 0x0000); // VDV[4:0] for VCOM amplitude  
	wr_reg(0x07, 0x0001);  
	delay_ms(200); // Dis-charge capacitor power voltage  
	wr_reg(0x10, 0x1090); // SAP, BT[3:0], AP, DSTB, SLP, STB  
	wr_reg(0x11, 0x0227); // Set DC1[2:0], DC0[2:0], VC[2:0]  
	delay_ms(50); // Delay 50ms  
	wr_reg(0x12, 0x001F); // 0012  
	delay_ms(50); // Delay 50ms  
	wr_reg(0x13, 0x1500); // VDV[4:0] for VCOM amplitude  
	wr_reg(0x29, 0x0027); // 04  VCM[5:0] for VCOMH  
	wr_reg(0x2B, 0x000D); // Set Frame Rate  
	delay_ms(50); // Delay 50ms  
	wr_reg(0x20, 0x0000); // GRAM horizontal Address  
	wr_reg(0x21, 0x0000); // GRAM Vertical Address  
	// ----------- Adjust the Gamma Curve ----------//  
	wr_reg(0x30, 0x0000);  
	wr_reg(0x31, 0x0707);  
	wr_reg(0x32, 0x0307);  
	wr_reg(0x35, 0x0200);  
	wr_reg(0x36, 0x0008);  
	wr_reg(0x37, 0x0004);  
	wr_reg(0x38, 0x0000);  
	wr_reg(0x39, 0x0707);  
	wr_reg(0x3C, 0x0002);  
	wr_reg(0x3D, 0x1D04);  
	//------------------ Set GRAM area ---------------//  
	wr_reg(0x50, 0x0000); // Horizontal GRAM Start Address  
	wr_reg(0x51, 0x00EF); // Horizontal GRAM End Address  
	wr_reg(0x52, 0x0000); // Vertical GRAM Start Address  
	wr_reg(0x53, 0x013F); // Vertical GRAM Start Address  
	wr_reg(0x60, 0xA700); // Gate Scan Line  
	wr_reg(0x61, 0x0001); // NDL,VLE, REV   
	wr_reg(0x6A, 0x0000); // set scrolling line  
	//-------------- Partial Display Control ---------//  
	wr_reg(0x80, 0x0000);  
	wr_reg(0x81, 0x0000);  
	wr_reg(0x82, 0x0000);  
	wr_reg(0x83, 0x0000);  
	wr_reg(0x84, 0x0000);  
	wr_reg(0x85, 0x0000);  
	//-------------- Panel Control -------------------//  
	wr_reg(0x90, 0x0010);  
	wr_reg(0x92, 0x0600);  
	wr_reg(0x07, 0x0133); // 262K color and display ON  
	

	
  wr_reg(0x0000, 0x0001);                   
  delay_ms(10);                              

  wr_reg(0x00E3, 0x3008);
  wr_reg(0x00E7, 0x0012);
  wr_reg(0x00EF, 0x1231);
           
  wr_reg(0x0000, 0x0001);                    //start internal osc
  wr_reg(DRIVER_OUTPUT_CONTROL_1, 0x0100);        //SM = 0, SS = 1
  wr_reg(LCD_DRIVING_CONTROL, 0x0700);          //B/C = 1, EOR = 1                     
  wr_reg(ENTRY_MODE, 0x1030);                  //
  wr_reg(RESIZE_CONTROL, 0x0000);                  //RSZ0 = 0, RSZ1 = 0, RCH0 = 0, RCH1 = 0, RCV0 = 0, RCV1 = 0         
  wr_reg(DISPLAY_CONTROL_2, 0x0202);                 //BP[3:0] = 0010, FP[3:0] = 0010
  wr_reg(DISPLAY_CONTROL_3, 0x0000);               //PTS[2:0] = 000, PTG[1:0] = 00, ISC[3:0] = 0000
  wr_reg(DISPLAY_CONTROL_4, 0x0000);             //FMI[2:0] = 000 (???????? ?????? - 1 ?????),
                                                //FMARKOE = 0 (FMARK ?????? ????????)         
  wr_reg(RGB_DISPLAY_INTERFACE_CONTROL_1, 0x0000);   //RIM[1:0] = 00 (18-bit RGB ?????????),
                                                //DM[1:0] = 00 (?????????? ????????????),
                                                //RM = 0 (????????? ?????????/VSYNC ?????????),
                                                //ENC[2:0] = 000 (1 ???? ?????? ? GRAM)           
  wr_reg(FRAME_MARKER_POSITION, 0x0000);          //FMP[8:0] = 000000000 (??????? ?????? FMARK - ?????? 0)         
  wr_reg(RGB_DISPLAY_INTERFACE_CONTROL_2, 0x0000);   //DPL = 0 (???? ?????? ?? ???????????? ?????? DOTCLK),
                                                //EPL = 0 (?????? ?????? ??? ENABLE = 0),
                                                //HSPL = 0 (???????? ??????? HSYNC - ??????),
                                                //VSPL = 0 (???????? ??????? VSYNC - ??????)
  wr_reg(POWER_CONTROL_1, 0x0000);               //STB = 0 (standby mode ????????),
                                                //SLP = 0 (sleep mode ????????),
                                                //DSTB = 0 (deep standby mode ????????),
                                                //AP[2:0] = 000 (????????? gamma driver - ???????????; ????????? source driver - ???????????),
                                                //APE = 0 (power supply ????????),
                                                //BT[2:0] = 000 (DDVDH = Vci1*2, VCL = -Vci1, VGH = Vci1*6, VGL = -Vci1*5),
                                                //SAP = 0
  wr_reg(POWER_CONTROL_2, 0x0007);               //VC[2:0] = 111 (Vci1 = Vci*1,0),
                                                //DC0[2:0] = 000 (Fdcdc1 = Fosc),
                                                //DC1[2:0] = 000 (Fdcdc2 = Fosc/4)
  wr_reg(POWER_CONTROL_3, 0x0000);                 //VRH[3:0] = 0000 (VREG1OUT - ??????????),
                                                //VCIRE = 0 (??????? ???????? ?????????? Vci),
                                                //PON = 0 (VGL ????? ????????)                                               
  wr_reg(POWER_CONTROL_4, 0x0000);               //VDV[4:0] = 00000 (Vcom = VREG1OUT*0,70)
  wr_reg(DISPLAY_CONTROL_1, 0x0001);               //D[1:0] = 01 (source = GND, ????? Vcom = GND, ?????????? ????????),
                                                //CL = 0 (262144 ?????),
                                                //DTE = 0, GON = 0 (????? gate G1~G320 = VGH),
                                                //BASEE = 0 (base image ????????),
                                                //PTDE[1:0] = 00 (partial image 1 ? partial image 2 ?????????)
                       
  delay_ms(50);                                 //????????

  wr_reg(POWER_CONTROL_1, 0x1090);               //STB = 0 (standby mode ????????),
                                                //SLP = 0 (sleep mode ????????),
                                                //DSTB = 0 (deep standby mode ????????),
                                                //AP[2:0] = 001 (????????? gamma driver -> 1,0; ????????? source driver -> 1,0),
                                                //APE = 1 (power supply ????????),
                                                //BT[2:0] = 000 (DDVDH = Vci1*2, VCL = -Vci1, VGH = Vci1*6, VGL = -Vci1*5),
                                                //SAP = 1 (source driver ????????)
  wr_reg(POWER_CONTROL_2, 0x0227);               //VC[2:0] = 111 (Vci1 = Vci*1,0),
                                                //DC0[2:0] = 010 (Fdcdc1 = Fosc/4),
                                                //DC1[2:0] = 010 (Fdcdc2 = Fosc/16)

  delay_ms(50);                                 //????????

  wr_reg(POWER_CONTROL_3, 0x001f);             //VRH[3:0] = 1111 (VREG1OUT = Vci*1,95),
                                                //VCIRE = 0 (??????? ???????? ?????????? Vci),
                                                //PON = 1 (VGL ????? ????????)
                       
  delay_ms(50);                                 //????????

  wr_reg(POWER_CONTROL_4, 0x1500);               //VDV[4:0] = 10101 (Vcom = VREG1OUT*1,04)
  wr_reg(POWER_CONTROL_7, 0x0027);               //VCM[5:0] = 010111 (VcomH = VREG1OUT*0,8)
  wr_reg(FRAME_RATE_COLOR_CONTROL, 0x000d);      //FRS[3:0] = 1101 (frame rate = 128)

  delay_ms(50);                                 //????????

  wr_reg(HORIZONTAL_ADDRESS_SET, 0x0000);          //AD[16:0] = 00000000000000000                                                   
  wr_reg(VERTICAL_ADDRESS_SET, 0x0000);          //AD[16:0] = 00000000000000000
             
  delay_ms(50);                                 //????????

  wr_reg(GAMMA_CONTROL_1, 0x0000);             //KP1[2:0] = 000, KP0[2:0] = 000
  wr_reg(GAMMA_CONTROL_2, 0x0707);               //KP3[2:0] = 111, KP2[2:0] = 111
  wr_reg(GAMMA_CONTROL_3, 0x0307);               //KP5[2:0] = 011, KP4[2:0] = 111
  wr_reg(GAMMA_CONTROL_4, 0x0200);               //RP1[2:0] = 010, RP0[2:0] = 000
  wr_reg(GAMMA_CONTROL_5, 0x0008);             //VRP1[4:0] = 00000, VRP0[3:0] = 1000
  wr_reg(GAMMA_CONTROL_6, 0x0004);               //KN1[2:0] = 000, KN0[2:0] = 100
  wr_reg(GAMMA_CONTROL_7, 0x0000);                 //KN3[2:0] = 000, KN2[2:0] = 000
  wr_reg(GAMMA_CONTROL_8, 0x0707);              //KN5[2:0] = 111, KN4[2:0] = 111
  wr_reg(GAMMA_CONTROL_9, 0x0002);               //RN1[2:0] = 000, RN0[2:0] = 010
  wr_reg(GAMMA_CONTROL_10, 0x1d04);            //VRN1[4:0] = 11101, VRN0[3:0] = 0100

  delay_ms(50);                                 //????????

  wr_reg(WINDOW_HORIZONTAL_ADDRESS_START, 0x0000);           //HSA[7:0] = 00000000
  wr_reg(WINDOW_HORIZONTAL_ADDRESS_END, 0x00ef);         //HEA[7:0] = 11101111
  wr_reg(WINDOW_VERTICAL_ADDRESS_START, 0x0000);           //VSA[8:0] = 000000000
  wr_reg(WINDOW_VERTICAL_ADDRESS_END, 0x013f);            //VEA[8:0] = 100111111
  wr_reg(GATE_SCAN_CONTROL_1, 0xa700);                    //SCN[5:0] = 000000 (???????????? ? G320),
                                                      //NL[5:0] = 100111 (320 ????? LCD),
                                                      //GS = 1 (???????????? G320~G1)
  wr_reg(GATE_SCAN_CONTROL_2, 0x0001);                //NDL = 0 (V63 - ?????????????, V0 - ?????????????),
                                                      //VLE = 0 (???????????? ????????? ?????????),
                                                      //REV = 1 (???????? ????? ??????)
  wr_reg(GATE_SCAN_CONTROL_3, 0x0000);                  //VL[8:0] = 000000000 (0 ????? ?????????)

  wr_reg(PARTIAL_IMAGE_1_DISPLAY_POSITION, 0x0000);
  wr_reg(PARTIAL_IMAGE_1_RAM_START_LINE_ADDRESS, 0x0000);   
  wr_reg(PARTIAL_IMAGE_1_RAM_END_LINE_ADDRESS, 0x0000);
  wr_reg(PARTIAL_IMAGE_2_DISPLAY_POSITION, 0x0000);
  wr_reg(PARTIAL_IMAGE_2_RAM_START_LINE_ADDRESS, 0x0000);
  wr_reg(PARTIAL_IMAGE_2_RAM_END_LINE_ADDRESS, 0x0000);
     
  wr_reg(PANEL_INTERFACE_CONTROL_1, 0x0010);               //RTNI[4:0] = 10000 (16 ?????? ?? ??????),
                                                      //DIVI[1:0] = 00 (????????? ???????? ??????? Fosc)
  wr_reg(PANEL_INTERFACE_CONTROL_2, 0x0600);              //NOWI[2:0] = 101 (5 ?????? ??????? ?????? gate)

  wr_reg(DISPLAY_CONTROL_1, 0x0133);                  //D[1:0] = 11 (??????????? base image, ?????????? ????????),
                                                      //CL = 0 (262144 ?????),
                                                      //DTE = 1, GON = 1 (?????????? ???????????),
                                                      //BASEE = 1 (base image ????????),
                                                      //PTDE[1:0] = 00 (partial image 1 ? partial image 2 ?????????)
   
  wr_reg(HORIZONTAL_ADDRESS_SET, 0x0000);                  //AD[16:0] = 00000000000000000                                         
  wr_reg(VERTICAL_ADDRESS_SET, 0x0000);               //AD[16:0] = 00000000000000000
	*/

}

void ili9325::index(uint16_t indx)
{
	//отправляем команду
	pinCommand1.clearPin(CS);
	pinCommand2.clearPin(RS);	
	pinDataLow1.clearPort (0x000F);
	pinDataLow1.clearPort (0x00F0);
	pinDataHigh1.clearPort (0x0F00);
	pinDataHigh2.clearPort (0x0F00);	
	pinDataLow1.setValPort(indx & 0x000F);
	pinDataLow2.setValPort(indx & 0x00F0);
	pinCommand2.clearPin(WR);
	delay_us(5);
	pinCommand2.setPin(WR);
	pinCommand1.setPin(CS);	
}
void ili9325::data(uint16_t dta)
{
	//отправляем данные
	pinCommand1.clearPin(CS);
	pinCommand2.setPin(RS);
	pinDataLow1.clearPort (0x000F);
	pinDataLow1.clearPort (0x00F0);
	pinDataHigh1.clearPort (0x0F00);
	pinDataHigh2.clearPort (0x0F00);	
	pinDataLow1.setValPort(dta & 0x000F);
	pinDataLow2.setValPort(dta & 0x00F0);
	pinDataHigh1.setValPort (dta & 0x0F00);
	pinDataHigh2.setValPort ((dta & 0xF000)>>4);
	pinCommand2.clearPin(WR);
	delay_us(5);
	pinCommand2.setPin(WR);
	pinCommand1.setPin(CS);
	
}

void ili9325::wr_reg (uint16_t indx , uint16_t dta)
{
	pinCommand1.clearPin(CS);
	index (indx);
	data (dta);
	pinCommand1.setPin(CS);
}
/*
void ili9325::wr_reg (uint16_t indx , uint16_t dta)
{
	pinCommand1.clearPin(CS);
	pinCommand2.clearPin(RS);	
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
	pinCommand2.setPin(RS);
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


