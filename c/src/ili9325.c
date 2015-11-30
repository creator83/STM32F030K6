#include "ili9325.h"

void ili9325_init (void)
{
	//Tact Port A
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//Settings pins
	GPIOA->MODER &= ~(GPIO_MODER_MODER12|0x00FFFFFF);
	GPIOA->MODER |= (GPIO_MODER_MODER12_0|0x00555555);
	GPIOA->OTYPER &= ~0x1FFF;
	GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEEDR12|0x00FFFFFF);
	GPIOA->ODR |= 1 << WR;
	GPIOA->ODR |= 1 << RD;
	GPIOA->ODR |= 1 << CS;
	GPIOA->ODR |= 1 << RESET;
	GPIOA->ODR &= ~(1 << RS);
	
	
	//Turn on ili9325
	GPIOA->ODR &= ~(1 << RESET);
	delay_ms (100);
	GPIOA->ODR |= (1 << RESET);
	delay_ms (100);
	
	
	//===Sequence turn on===//
	ili9325_wr_reg(0xE3, 0x3008); // Set internal timing
	ili9325_wr_reg(0xE7, 0x0012); // Set internal timing
	ili9325_wr_reg(0xEF, 0x1231); // Set internal timing
	ili9325_wr_reg(0x01, 0x0100); // set SS and SM bit
	ili9325_wr_reg(0x02, 0x0700); // set 1 line inversion
	ili9325_wr_reg(0x03, 0x1020); // set GRAM write direction and BGR=1.
	ili9325_wr_reg(0x04, 0x0000); // Resize register
	ili9325_wr_reg(0x08, 0x0202); // set the back porch and front porch
	ili9325_wr_reg(0x09, 0x0000); // set non-display area refresh cycle ISC[3:0]
	ili9325_wr_reg(0x0A, 0x0000); // FMARK function
	ili9325_wr_reg(0x0C, 0x0000); // RGB interface setting
	ili9325_wr_reg(0x0D, 0x0000); // Frame marker Position
	ili9325_wr_reg(0x0F, 0x0000); // RGB interface polarity

	/*************Power On sequence ****************/

	ili9325_wr_reg(0x10, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	ili9325_wr_reg(0x11, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	ili9325_wr_reg(0x12, 0x0000); // VREG1OUT voltage
	ili9325_wr_reg(0x13, 0x0000); // VDV[4:0] for VCOM amplitude
	delay_ms(200); // Dis-charge capacitor power voltage
	ili9325_wr_reg(0x10, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
	ili9325_wr_reg(0x11, 0x0227); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	delay_ms(50); // Delay 50ms
	ili9325_wr_reg(0x12, 0x001C); // External reference voltage= Vci;
	delay_ms(50); // Delay 50ms
	ili9325_wr_reg(0x13, 0x1800); // R13=1200 when R12=009D;VDV[4:0] for VCOM amplitude
	ili9325_wr_reg(0x29, 0x001C); // R29=000C when R12=009D;VCM[5:0] for VCOMH
	ili9325_wr_reg(0x2B, 0x000D); // Frame Rate = 91Hz
	delay_ms(50); // Delay 50ms
	ili9325_wr_reg(0x20, 0x0000); // GRAM horizontal Address
	ili9325_wr_reg(0x21, 0x0000); // GRAM Vertical Address

	/************Adjust the Gamma Curve************/

	ili9325_wr_reg(0x30, 0x0007);
	ili9325_wr_reg(0x31, 0x0302);
	ili9325_wr_reg(0x32, 0x0105);
	ili9325_wr_reg(0x35, 0x0206);
	ili9325_wr_reg(0x36, 0x0808);
	ili9325_wr_reg(0x37, 0x0206);
	ili9325_wr_reg(0x38, 0x0504);
	ili9325_wr_reg(0x39, 0x0007);
	ili9325_wr_reg(0x3C, 0x0105);
	ili9325_wr_reg(0x3D, 0x0808);

	/************Set GRAM area ************/

	ili9325_wr_reg(0x50, 0x0000); // Horizontal GRAM Start Address
	ili9325_wr_reg(0x51, 0x00EF); // Horizontal GRAM End Address
	ili9325_wr_reg(0x52, 0x0000); // Vertical GRAM Start Address
	ili9325_wr_reg(0x53, 0x013F); // Vertical GRAM Start Address
	ili9325_wr_reg(0x60, 0xA700); // Gate Scan Line
	ili9325_wr_reg(0x61, 0x0001); // NDL,VLE, REV
	ili9325_wr_reg(0x6A, 0x0000); // set scrolling line

	/************ Partial Display Control ************/

	ili9325_wr_reg(0x80, 0x0000);
	ili9325_wr_reg(0x81, 0x0000);
	ili9325_wr_reg(0x82, 0x0000);
	ili9325_wr_reg(0x83, 0x0000);
	ili9325_wr_reg(0x84, 0x0000);
	ili9325_wr_reg(0x85, 0x0000);

	/************ Panel Control ************/

	ili9325_wr_reg(0x90, 0x0010);
	ili9325_wr_reg(0x92, 0x0000);
	ili9325_wr_reg(0x93, 0x0003);
	ili9325_wr_reg(0x95, 0x0110);
	ili9325_wr_reg(0x97, 0x0000);
	ili9325_wr_reg(0x98, 0x0000);
	ili9325_wr_reg(0x07, 0x0133); // 262K color and display ON
	
}

void ili9325_index (uint8_t indx)
{
	GPIOA->ODR &= ~(1 << RS);
	//GPIOA->ODR &= ~(1 << CS);
	GPIOA->ODR &= ~(0xFF);
	GPIOA->ODR &= ~(1 << WR);
	GPIOA->ODR |= (1 << WR);
	GPIOA->ODR &= ~(0xFF);
	GPIOA->ODR |= indx;
	GPIOA->ODR &= ~(1 << WR);
	GPIOA->ODR |= (1 << WR);	
	//GPIOA->ODR |= (1 << CS);
}

void ili9325_data (uint16_t data)
{
	GPIOA->ODR |= (1 << RS);
	//GPIOA->ODR &= ~(1 << CS);
	GPIOA->ODR &= ~(0xFF);
	GPIOA->ODR |= (data >> 8);
	GPIOA->ODR &= ~(1 << WR);
	GPIOA->ODR |= (1 << WR);
	GPIOA->ODR &= ~(0xFF);
	GPIOA->ODR |= (uint8_t) data;
	GPIOA->ODR &= ~(1 << WR);
	GPIOA->ODR |= (1 << WR);	
	//GPIOA->ODR |= (1 << CS);
}

void ili9325_wr_reg (uint8_t indx, uint16_t data)
{
	GPIOA->ODR &= ~(1 << CS);
	ili9325_index (indx);
	ili9325_data (data);
	GPIOA->ODR |= (1 << CS);
}

void ili9325_set_cursor (uint16_t x , uint16_t y)
{
	ili9325_wr_reg (0x20, x);
	ili9325_wr_reg (0x21, y);
	//ili9325_index (0x22);
}

void ili9325_point (uint16_t x , uint16_t y, uint16_t color)
{
	ili9325_set_cursor (x, y);
	ili9325_wr_reg (0x22, color);
	//ili9325_data (color);
}

void ili9325_fill_screen (uint16_t color)
{
	long i;
	ili9325_set_cursor(0,0);
		for (i=0; i < (X_rezolution*Y_rezolution);++i)
	{
		ili9325_data (color);
	}
}




