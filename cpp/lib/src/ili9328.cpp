#include "ili9328.h"

ili9328::ili9328()
:pinData (Gpio::A), pinCommand (Gpio::A)
{
	//Settings pins
	pinData.setOutPort (0xFF);
	pinCommand.setOutPin (CS);
	pinCommand.setOutPin (RS);	
	pinCommand.setOutPin (WR);
	pinCommand.setOutPin (RD);	
	pinCommand.setOutPin (RST);	
	pinCommand.setPin (CS);
	pinCommand.setPin (RST);
	pinCommand.setPin (WR);
	pinCommand.setPin (RD);
	pinCommand.clearPin (RS);
	init();
}

void ili9328::init()
{
	pinCommand.clearPin (RST);
	delay_ms (100);
	pinCommand.setPin (RST);
	delay_ms (100);
	
	
		write_reg(0xE5, 0x78F0); // set SRAM internal timing
	write_reg(0x01, 0x0100); // set Driver Output Control  
	write_reg(0x02, 0x0700); // set 1 line inversion  
	write_reg(0x03, 0x1030); // set GRAM write direction and BGR=1.  
	write_reg(0x04, 0x0000); // Resize register  
	write_reg(0x08, 0x0207); // set the back porch and front porch  
	write_reg(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]  
	write_reg(0x0A, 0x0000); // FMARK function  
	write_reg(0x0C, 0x0000); // RGB interface setting  
	write_reg(0x0D, 0x0000); // Frame marker Position  
	write_reg(0x0F, 0x0000); // RGB interface polarity  
	//===Power On sequence ===//  
	write_reg(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB  
	write_reg(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]  
	write_reg(0x12, 0x0000); // VREG1OUT voltage  
	write_reg(0x13, 0x0000); // VDV[4:0] for VCOM amplitude  
	write_reg(0x07, 0x0001);  
	delay_ms(200); // Dis-charge capacitor power voltage  
	write_reg(0x10, 0x1090); // SAP, BT[3:0], AP, DSTB, SLP, STB  
	write_reg(0x11, 0x0227); // Set DC1[2:0], DC0[2:0], VC[2:0]  
	delay_ms(50); // Delay 50ms  
	write_reg(0x12, 0x001F); // 0012  
	delay_ms(50); // Delay 50ms  
	write_reg(0x13, 0x1500); // VDV[4:0] for VCOM amplitude  
	write_reg(0x29, 0x0027); // 04  VCM[5:0] for VCOMH  
	write_reg(0x2B, 0x000D); // Set Frame Rate  
	delay_ms(50); // Delay 50ms  
	write_reg(0x20, 0x0000); // GRAM horizontal Address  
	write_reg(0x21, 0x0000); // GRAM Vertical Address  
	// ----------- Adjust the Gamma Curve ----------//  
	write_reg(0x30, 0x0000);  
	write_reg(0x31, 0x0707);  
	write_reg(0x32, 0x0307);  
	write_reg(0x35, 0x0200);  
	write_reg(0x36, 0x0008);  
	write_reg(0x37, 0x0004);  
	write_reg(0x38, 0x0000);  
	write_reg(0x39, 0x0707);  
	write_reg(0x3C, 0x0002);  
	write_reg(0x3D, 0x1D04);  
	//------------------ Set GRAM area ---------------//  
	write_reg(0x50, 0x0000); // Horizontal GRAM Start Address  
	write_reg(0x51, 0x00EF); // Horizontal GRAM End Address  
	write_reg(0x52, 0x0000); // Vertical GRAM Start Address  
	write_reg(0x53, 0x013F); // Vertical GRAM Start Address  
	write_reg(0x60, 0xA700); // Gate Scan Line  
	write_reg(0x61, 0x0001); // NDL,VLE, REV   
	write_reg(0x6A, 0x0000); // set scrolling line  
	//-------------- Partial Display Control ---------//  
	write_reg(0x80, 0x0000);  
	write_reg(0x81, 0x0000);  
	write_reg(0x82, 0x0000);  
	write_reg(0x83, 0x0000);  
	write_reg(0x84, 0x0000);  
	write_reg(0x85, 0x0000);  
	//-------------- Panel Control -------------------//  
	write_reg(0x90, 0x0010);  
	write_reg(0x92, 0x0600);  
	write_reg(0x07, 0x0133); // 262K color and display ON  
	
	 /*  
	write_reg(0x00e7,0x0010);  
    write_reg(0x0000,0x0001);       
    write_reg(0x0001,0x0100);     
    write_reg(0x0002,0x0700);      
    write_reg(0x0003,(1<<12)|(1<<5)|(1<<4)|(0<<3) );       
    write_reg(0x0004,0x0000);                                   
    write_reg(0x0008,0x0207);               
    write_reg(0x0009,0x0000);         
    write_reg(0x000a,0x0000);              
    write_reg(0x000c,0x0001);              
    write_reg(0x000d,0x0000);                               
    write_reg(0x000f,0x0000);     
    write_reg(0x0010,0x0000);   
    write_reg(0x0011,0x0007);
    write_reg(0x0012,0x0000);                                                                 
    write_reg(0x0013,0x0000);  delay_ms(50);             
    write_reg(0x0010,0x1590);   
    write_reg(0x0011,0x0227);  delay_ms(50);        
    write_reg(0x0012,0x009c);  delay_ms(50);             
    write_reg(0x0013,0x1900);   
    write_reg(0x0029,0x0023);
    write_reg(0x002b,0x000e);  delay_ms(50);             
    write_reg(0x0020,0x0000);                                                            
    write_reg(0x0021,0x0000);  delay_ms(50);             
    write_reg(0x0030,0x0007); 
    write_reg(0x0031,0x0707);   
    write_reg(0x0032,0x0006);
    write_reg(0x0035,0x0704);
    write_reg(0x0036,0x1f04); 
    write_reg(0x0037,0x0004);
    write_reg(0x0038,0x0000);        
    write_reg(0x0039,0x0706);     
    write_reg(0x003c,0x0701);	
    write_reg(0x003d,0x000f);  delay_ms(50);         
    write_reg(0x0050,0x0000);        
    write_reg(0x0051,0x00ef);   
    write_reg(0x0052,0x0000);     
    write_reg(0x0053,0x013f);
    write_reg(0x0060,0xa700);        
    write_reg(0x0061,0x0001); 
    write_reg(0x006a,0x0000);
    write_reg(0x0080,0x0000);
    write_reg(0x0081,0x0000);
    write_reg(0x0082,0x0000);
    write_reg(0x0083,0x0000);
    write_reg(0x0084,0x0000);
    write_reg(0x0085,0x0000);
    write_reg(0x0090,0x0010);     
    write_reg(0x0092,0x0000);  
    write_reg(0x0093,0x0003);
    write_reg(0x0095,0x0110);
    write_reg(0x0097,0x0000);        
    write_reg(0x0098,0x0000);  
    write_reg(0x0007,0x0133);
    write_reg(0x0020,0x0000);                                                            
    write_reg(0x0021,0x0000);    
	

 write_reg(0x0001,0x0100); 
 write_reg(0x0002,0x0700); 
 write_reg(0x0003,0x1030); 
 write_reg(0x0004,0x0000); 
 write_reg(0x0008,0x0207);  
 write_reg(0x0009,0x0000);
 write_reg(0x000A,0x0000); 
 write_reg(0x000C,0x0000); 
 write_reg(0x000D,0x0000);
 write_reg(0x000F,0x0000);
//power on sequence VGHVGL
 write_reg(0x0010,0x0000);   
 write_reg(0x0011,0x0007);  
 write_reg(0x0012,0x0000);  
 write_reg(0x0013,0x0000); 
//vgh 
 write_reg(0x0010,0x1290);   
 write_reg(0x0011,0x0227);
 delay_ms(100);
 //vregiout 
 write_reg(0x0012,0x001d); //0x001b
 delay_ms(100); 
 //vom amplitude
 write_reg(0x0013,0x1500);
 delay_ms(100); 
 //vom H
 write_reg(0x0029,0x0018); 
 write_reg(0x002B,0x000D); 

//gamma
 write_reg(0x0030,0x0004);
 write_reg(0x0031,0x0307);
 write_reg(0x0032,0x0002);// 0006
 write_reg(0x0035,0x0206);
 write_reg(0x0036,0x0408);
 write_reg(0x0037,0x0507); 
 write_reg(0x0038,0x0204);//0200
 write_reg(0x0039,0x0707); 
 write_reg(0x003C,0x0405);// 0504
 write_reg(0x003D,0x0F02); 
 //ram
 write_reg(0x0050,0x0000); 
 write_reg(0x0051,0x00EF);
 write_reg(0x0052,0x0000); 
 write_reg(0x0053,0x013F);  
 write_reg(0x0060,0xA700); 
 write_reg(0x0061,0x0001); 
 write_reg(0x006A,0x0000); 
 //
 write_reg(0x0080,0x0000); 
 write_reg(0x0081,0x0000); 
 write_reg(0x0082,0x0000); 
 write_reg(0x0083,0x0000); 
 write_reg(0x0084,0x0000); 
 write_reg(0x0085,0x0000); 
 //
 write_reg(0x0090,0x0010); 
 write_reg(0x0092,0x0600); 
 write_reg(0x0093,0x0003); 
 write_reg(0x0095,0x0110); 
 write_reg(0x0097,0x0000); 
 write_reg(0x0098,0x0000);
 write_reg(0x0007,0x0133);
 write_index(0x22);
 //write_reg(0x0022);//	
	
	
	
	
write_reg(0x00E3,0x3008);                          //set the internal timing
write_reg(0x00E7,0x0012);                          //set the internal timing
write_reg(0x00EF,0x1231);                          //set the internal timing
write_reg(TS_INS_START_OSC,0x0001);                //start oscillator
delay_ms(50);
write_reg(TS_INS_DRIV_OUT_CTRL,0x0100);            //set SS, SM
write_reg(TS_INS_DRIV_WAV_CTRL,0x0700);            //set 1 line inversion
write_reg(TS_INS_ENTRY_MOD,TS_VAL_ENTRY_MOD);      //set GRAM write direction, BGR=0
write_reg(TS_INS_RESIZE_CTRL,0x0000);              //no resizing
write_reg(TS_INS_DISP_CTRL2,0x0202);               //front & back porch periods = 2
write_reg(TS_INS_DISP_CTRL3,0x0000);
write_reg(TS_INS_DISP_CTRL4,0x0000);
//
 write_reg(TS_INS_RGB_DISP_IF_CTRL1,0x0000);
write_reg(TS_INS_FRM_MARKER_POS,0x0000);
write_reg(TS_INS_RGB_DISP_IF_CTRL2,0x0000);
write_reg(TS_INS_POW_CTRL1,0x0000);
write_reg(TS_INS_POW_CTRL2,0x0007);
write_reg(TS_INS_POW_CTRL3,0x0000);
write_reg(TS_INS_POW_CTRL4,0x0000);
delay_ms(200);
write_reg(TS_INS_POW_CTRL1,0x1690);
write_reg(TS_INS_POW_CTRL2,0x0227); //(0x0137);
delay_ms(50);
write_reg(TS_INS_POW_CTRL3,0x001A); //(0x013C);
delay_ms(50);
write_reg(TS_INS_POW_CTRL4,0x1800); //(0x1400);
write_reg(TS_INS_POW_CTRL7,0x002A); //(0x0007);
delay_ms(50);
write_reg(TS_INS_GRAM_HOR_AD,0x0000);
write_reg(TS_INS_GRAM_VER_AD,0x0000);
write_reg(TS_INS_GAMMA_CTRL1,0x0007);
write_reg(TS_INS_GAMMA_CTRL2,0x0605);
write_reg(TS_INS_GAMMA_CTRL3,0x0106);
write_reg(TS_INS_GAMMA_CTRL4,0x0206);
write_reg(TS_INS_GAMMA_CTRL5,0x0808);
write_reg(TS_INS_GAMMA_CTRL6,0x0007);
write_reg(TS_INS_GAMMA_CTRL7,0x0201);
write_reg(TS_INS_GAMMA_CTRL8,0x0007);
write_reg(TS_INS_GAMMA_CTRL9,0x0602);
write_reg(TS_INS_GAMMA_CTRL10,0x0808);
write_reg(TS_INS_HOR_START_AD,0x0000);
write_reg(TS_INS_HOR_END_AD,0x00EF);
write_reg(TS_INS_VER_START_AD,0x0000);
write_reg(TS_INS_VER_END_AD,0x013F);
write_reg(TS_INS_GATE_SCAN_CTRL1,0xA700);
write_reg(TS_INS_GATE_SCAN_CTRL2,0x0001);
write_reg(TS_INS_GATE_SCAN_CTRL3,0x0000);
write_reg(TS_INS_PART_IMG1_DISP_POS,0x0000);
write_reg(TS_INS_PART_IMG1_START_AD,0x0000);
write_reg(TS_INS_PART_IMG1_END_AD,0x0000);
write_reg(TS_INS_PART_IMG2_DISP_POS,0x0000);
write_reg(TS_INS_PART_IMG2_START_AD,0x0000);
write_reg(TS_INS_PART_IMG2_END_AD,0x0000);
write_reg(TS_INS_PANEL_IF_CTRL1,0x0010);
write_reg(TS_INS_PANEL_IF_CTRL2,0x0000);
write_reg(TS_INS_PANEL_IF_CTRL3,0x0003);
write_reg(TS_INS_PANEL_IF_CTRL4,0x0110);
write_reg(TS_INS_PANEL_IF_CTRL5,0x0000);
write_reg(TS_INS_PANEL_IF_CTRL6,0x0000);
write_reg(TS_INS_DISP_CTRL1,0x0133);


	//=== Start Initial Sequence ===//

	write_reg(0xE3, 0x3008); // Set internal timing
	write_reg(0xE7, 0x0012); // Set internal timing
	write_reg(0xEF, 0x1231); // Set internal timing
	write_reg(0x01, 0x0100); // set SS and SM bit
	write_reg(0x02, 0x0700); // set 1 line inversion
	write_reg(0x03, 0x1020); // set GRAM write direction and BGR=1.
	write_reg(0x04, 0x0000); // Resize register
	write_reg(0x08, 0x0202); // set the back porch and front porch
	write_reg(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]
	write_reg(0x0A, 0x0000); // FMARK function
	write_reg(0x0C, 0x0000); // RGB interface setting
	write_reg(0x0D, 0x0000); // Frame marker Position
	write_reg(0x0F, 0x0000); // RGB interface polarity

	//=== Power On sequence ===//

	write_reg(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	write_reg(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	write_reg(0x12, 0x0000); // VREG1OUT voltage
	write_reg(0x13, 0x0000); // VDV[4:0] for VCOM amplitude
	delay_ms(200); // Dis-charge capacitor power voltage
	write_reg(0x10, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
	write_reg(0x11, 0x0227); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	delay_ms(50); // Delay 50ms
	write_reg(0x12, 0x001C); // External reference voltage= Vci;
	delay_ms(50); // Delay 50ms
	write_reg(0x13, 0x1800); // R13=1200 when R12=009D;VDV[4:0] for VCOM amplitude
	write_reg(0x29, 0x001C); // R29=000C when R12=009D;VCM[5:0] for VCOMH
	write_reg(0x2B, 0x000D); // Frame Rate = 91Hz
	delay_ms(50); // Delay 50ms
	write_reg(0x20, 0x0000); // GRAM horizontal Address
	write_reg(0x21, 0x0000); // GRAM Vertical Address

	//=== Adjust the Gamma Curve ===//

	write_reg(0x30, 0x0007);
	write_reg(0x31, 0x0302);
	write_reg(0x32, 0x0105);
	write_reg(0x35, 0x0206);
	write_reg(0x36, 0x0808);
	write_reg(0x37, 0x0206);
	write_reg(0x38, 0x0504);
	write_reg(0x39, 0x0007);
	write_reg(0x3C, 0x0105);
	write_reg(0x3D, 0x0808);

	//=== Set GRAM area ===//

	write_reg(0x50, 0x0000); // Horizontal GRAM Start Address
	write_reg(0x51, 0x00EF); // Horizontal GRAM End Address
	write_reg(0x52, 0x0000); // Vertical GRAM Start Address
	write_reg(0x53, 0x013F); // Vertical GRAM Start Address
	write_reg(0x60, 0xA700); // Gate Scan Line
	write_reg(0x61, 0x0001); // NDL,VLE, REV
	write_reg(0x6A, 0x0000); // set scrolling line

	//=== Partial Display Control ===//

	write_reg(0x80, 0x0000);
	write_reg(0x81, 0x0000);
	write_reg(0x82, 0x0000);
	write_reg(0x83, 0x0000);
	write_reg(0x84, 0x0000);
	write_reg(0x85, 0x0000);

	//=== Panel Control ===//

	write_reg(0x90, 0x0010);
	write_reg(0x92, 0x0000);
	write_reg(0x93, 0x0003);
	write_reg(0x95, 0x0110);
	write_reg(0x97, 0x0000);
	write_reg(0x98, 0x0000);
	write_reg(0x07, 0x0133); // 262K color and display ON*/
}

void ili9328::write_index (uint16_t index)
{
		//?????????? ???????
	pinCommand.clearPin(CS);
	pinCommand.clearPin(RS);	
	pinData.clearPort(0xFF);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);	
	pinData.setValPort(index);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}

void ili9328::write_data (uint16_t data)
{
		//?????????? ??????
	pinCommand.clearPin(CS);
	pinCommand.setPin(RS);
	pinData.clearPort(0xFF);
	pinData.setValPort(data>>8);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);
	pinData.clearPort(0xFF);
	pinData.setValPort(data);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}
/*
void ili9328::write_reg (uint16_t _reg , uint16_t _data)
{
	write_index (_reg);
	write_data (_data);
}
*/
void ili9328::write_reg (uint16_t _reg , uint16_t _data)
{
	pinCommand.clearPin(CS);
	pinCommand.clearPin(RS);	
	pinData.clearPort(0xFF);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);	
	pinData.setValPort(_reg);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);
	delay_us(5);	
	pinCommand.setPin(RS);
	pinData.clearPort(0xFF);
	pinData.setValPort(_data>>8);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);
	pinData.clearPort(0xFF);
	pinData.setValPort(_data);
	pinCommand.clearPin(WR);
	delay_us(5);
	pinCommand.setPin(WR);
	pinCommand.setPin(CS);
}

void ili9328::point (uint16_t x, uint16_t y , uint16_t c)
{
	
}

void ili9328::set_cursor (uint16_t x , uint16_t y)
{
	write_reg (0x20 , x);
	write_reg(0x21 , y);
	write_index(0x22);
}

void ili9328::clear (uint16_t c)
{

}

void ili9328::fill_screen (uint16_t color)
{
	set_cursor(0,0);
	for (long i=0;i<76800;++i)
	{
		write_data(color);
	}		
}
