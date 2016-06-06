#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "Spi.h"
#include "nrf24l01.h"
#include "pcd8544.h"
#include "systimer.h"
#include "dma.h"
#include <vector>


typedef unsigned int* reg;

extern "C"
{
	void DMA1_Channel2_3_IRQHandler(void);
	void DMA1_Channel4_5_IRQHandler(void);
	void SysTick_Handler (void);
}

tact frq;
pcd8544 lcd;
const uint16_t length = 504;

const char pic [length] = {0x98, 0x98, 0x98, 0x88, 0x9C, 0x94, 0x84, 0x06, 0x06, 0x06, 0x02, 0x02, 0x07, 0x05, 0x05, 0x09, 0x49, 0x41, 0x41, 0x41, 0x41, 0x41, 0x42, 0x42, 0x43, 0x49, 0x48, 0x49, 0xC0, 0xC0, 0x80, 0x80, 0x18, 0x08, 0x88, 0xC0, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xE0, 0xC0, 0xC0, 0x60, 0x60, 0xA0, 0x60, 0x60, 0x80, 0x80, 0x20, 0x40, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0xBC, 0xB4, 0xAC, 0x94, 0xC0, 0xCC, 0xE4, 0xE4, 0xE4, 0xE8, 0xE2, 0xF7, 0xF3, 0x62, 0x60, 0x60, 0x6C, 0xFC, 0xFF, 0xB7, 0x9D, 0x9D, 0xCD, 0xCD, 0x4B, 0x4B, 0x22, 0x36, 0x16, 0x53, 0x4B, 0x5B, 0x5B, 0x53, 0x41, 0xC1, 0xE1, 0xC4, 0xA3, 0xA3, 0xEB, 0xE7, 0xF6, 0xFA, 0x69, 0xFC, 0x7C, 0xB4, 0xBC, 0xBC, 0xBE, 0x3E, 0x37, 0xBE, 0x32, 0x32, 0x12, 0x1A, 0x53, 0x59, 0x48, 0x89, 0x98, 0x80, 0xE0, 0xE0, 0x68, 0x20, 0xF0, 0x80, 0xC0, 0x40, 0x40, 0x60, 0x60, 0x60, 0x20, 0x20, 0x20, 0x20, 0x30, 0x10, 0x10, 0x10,
	0x7A, 0xFF, 0x7F, 0x7F, 0x77, 0xF7, 0x25, 0x3D, 0x2D, 0x1C, 0x94, 0x9C, 0x1A, 0x1A, 0x12, 0x1A, 0x0E, 0x0E, 0x0E, 0x0E, 0x0F, 0x0F, 0x8F, 0xCC, 0xAE, 0x3E, 0xCF, 0xA6, 0x3E, 0x5E, 0x36, 0x4D, 0x4B, 0x1B, 0xB7, 0xA7, 0x37, 0x13, 0x93, 0x03, 0x01, 0x11, 0x99, 0xD9, 0xE1, 0xE9, 0x6D, 0x25, 0x21, 0x11, 0x11, 0x80, 0xC0, 0x41, 0x40, 0x40, 0x46, 0x46, 0x80, 0xC8, 0xC8, 0x98, 0xD0, 0x90, 0xD8, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x38, 0x00, 0x40, 0x42, 0x02, 0x0A, 0x0C, 0x0E, 0xBA, 0x58, 0xDB, 0xD9, 0x9B, 0x1D, 0x1D, 0x1C, 0x1E, 0x1E, 0x2E, 0x6E, 0x6F, 0xED, 0xEF, 0x6E, 0x6E, 0x3F, 0x1D, 0x1D, 0x52, 0x5B, 0x4B, 0xAB, 0xEF, 0x6B, 0x6F, 0x97, 0x17, 0x07, 0x02, 0xC3, 0x42, 0x6E, 0x6E, 0x7F, 0x5D, 0xF5, 0xAD, 0x8D, 0x0F, 0x8E, 0x0E, 0x02, 0x02, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x20, 0x60, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0xC0, 0x40, 0x01, 0x00, 0x80, 0x80, 0x80, 0x81, 0x81, 0x80, 0x40, 0x49, 0x09, 0x81, 0xD9, 0x59, 0x03, 0x0B, 0x09, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x13, 0x13, 0x03, 0x8A, 0x4A, 0x46, 0x44, 0x05, 0x41, 0x41, 0x41, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x82, 0x82, 0xB3, 0xB1, 0x91, 0x81, 0x81, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x40, 0xE0, 0x60, 0x00, 0x20, 0x40, 0x00, 0x00, 0x00, 0x01, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x05, 0x03, 0x05, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
char pic1 [length]={0}	;

char buffer [length]={0}	;
const char pic2 []={
0x00,0x00,0x00,0x40,0x60,0x30,0x10,0x10,
0x30,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0xC0,0xE0,0xF0,
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0x00,0x00,0x40,0x60,0xF0,0xF0,0x00,0x00,
0x00,0x00,0x00,0xC0,0xE0,0x30,0x10,0x10,
0x30,0xE0,0xC0,0x00,0x00,0x40,0x60,0x30,
0x10,0x10,0x30,0xE0,0xC0,0x00,0x00,0x40,
0x60,0x30,0x10,0x10,0x30,0xE0,0xC0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,//1 bank
0x60,0x70,0x58,0x4C,0x46,0x43,0x41,0x00,
0x00,0x60,0x60,0x00,0x00,0x00,0x0C,0x0E,
0x0B,0x09,0x08,0x7F,0x7F,0x08,0x08,0x00,
0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,
0x7F,0x7F,0x00,0x00,0x00,0x00,0x00,0x1F,
0x3F,0x60,0x40,0x40,0x60,0x3F,0x1F,0x00,
0x00,0x40,0x60,0x70,0x58,0x4C,0x46,0x43,
0x41,0x00,0x00,0x10,0x30,0x60,0x42,0x42,
0x67,0x3D,0x18,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x7F,0x7F,0x00,0x00,0x00,0x00,//2 bank
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFE,0x90,0x08,0x08,0xF0,0x00,0xD0,0x28,
0x28,0xA8,0xF0,0x00,0xF8,0x10,0x08,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0x00,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,//3 bank
0x10,0x10,0x10,0x10,0x11,0x10,0x11,0x11,
0x10,0x10,0x10,0x11,0x91,0x90,0x91,0x90,
0x91,0x90,0x10,0x10,0x10,0x10,0x10,0x10,
0x90,0x90,0x90,0x9F,0x90,0x93,0x13,0x13,
0x13,0x13,0x13,0x13,0x13,0x13,0x13,0x13,
0x13,0x13,0x13,0x13,0x13,0x13,0x13,0x13,
0x93,0x93,0x93,0x13,0x13,0x13,0x13,0x93,
0x93,0x93,0x93,0x93,0x93,0x93,0x93,0x93,
0x93,0x93,0x13,0x13,0x13,0x13,0x13,0x13,
0x13,0x10,0x10,0x10,0x10,0x10,0x10,0x10,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//4 bank
0x00,0x00,0x00,0x00,0x00,0x0C,0x0F,0x0F,
0x03,0x01,0x81,0xC1,0xE3,0x7F,0x3F,0x1E,
0x00,0x00,0x06,0x07,0x07,0x63,0x61,0x61,
0x73,0xFF,0xFF,0xDE,0x00,0x00,0x00,0x00,
0x18,0x18,0x18,0x00,0x00,0x80,0xC0,0xE0,
0x70,0x3C,0x1E,0x0F,0xFF,0xFF,0xFF,0x00,
0x00,0x00,0x00,0x01,0x01,0x01,0x01,0xC1,
0xF1,0xFD,0x3F,0x0F,0x03,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//5bank
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x30,0x38,0x3C,0x3E,0x37,0x33,0x31,
0x30,0x30,0x30,0x30,0x00,0x00,0x0C,0x1C,
0x3C,0x38,0x30,0x30,0x30,0x38,0x1F,0x1F,
0x07,0x00,0x00,0x00,0x30,0x30,0x30,0x00,
0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
0x3F,0x3F,0x3F,0x03,0x03,0x00,0x00,0x00,
0x00,0x38,0x3F,0x3F};

const char pic3 []={
0x01,0x03,0x07,0x0F,0x1F,0x3F,0x4F,0x63,
0x6D,0x61,0x4F,0x7F,0x4B,0x55,0x55,0x43,
0x5F,0x7F,0x41,0x55,0x55,0x4B,0x7F,0x5F,
0x43,0x7D,0x21,0x1F,0x0F,0x07,0x03,0x01,
0xFF,0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,
0x7F,0x79,0x57,0x57,0x61,0x7F,0x41,0x75,
0x75,0x73,0x7F,0x63,0x5D,0x5D,0x63,0x7F,
0x41,0x55,0x55,0x4B,0x7F,0x41,0x55,0x55,
0x55,0x7F,0x41,0x77,0x77,0x41,0x7F,0x41,
0x57,0x57,0x6F,0x7F,0x7F,0x7F,0x3F,0x1F,
0x0F,0x07,0x03,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x0F,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,
0x08,0x08,0x08,0x08,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


void init_dma_spi_tx ();
void init_dma_mem ();
void pic_shift (uint8_t sh);
//uint8_t 
const char * arr [4] = {pic, pic1, pic2, pic3};

	
void DMA1_Channel2_3_IRQHandler(void)
{
	DMA1->IFCR |= DMA_IFCR_CTCIF3|DMA_IFCR_CGIF3|DMA_IFCR_CHTIF3;
	DMA1_Channel3->CCR &= ~ DMA_CCR_EN;	
	while (lcd.spi_bsy());
	lcd.desassert_chip ();
	
	/*lcd.clear_screen();
	lcd.string_buffer (25,3, "DONE");
	lcd.draw_buffer ();	
	delay_ms (3000);*/
}

void DMA1_Channel4_5_IRQHandler(void)
{
	DMA1->IFCR |= DMA_IFCR_CTCIF5|DMA_IFCR_CGIF5|DMA_IFCR_CHTIF5;
	DMA1_Channel5->CCR &= ~ DMA_CCR_EN;
	lcd.string_screen (10,1, "COPY_DMA_SPI");
	DMA1_Channel3->CMAR = (uint32_t) (arr[0]);
	DMA1_Channel3->CNDTR = length;
	delay_ms (1000);
	lcd.gotoxy (0,0);
	lcd.assert_chip();
	DMA1_Channel3->CCR |= DMA_CCR_EN;
}

void SysTick_Handler (void)
{
	
}


int main()
{
	systimer sys(systimer::ms, 1);
	//init_dma_spi_tx ();
	init_dma_mem ();
	dma spi_screen (dma::ch3, dma::mem2periph, dma::SPI1_TX);
	spi_screen.set_periph ((uint32_t)&SPI1->DR);
	spi_screen.set_mem ((uint32_t)pic);
	spi_screen.set_inc_mem (true);
	
	
	lcd.draw_big_number (10,0,2);
	lcd.draw_big_number (25,0,3);
	lcd.draw_big_number (40,0,6);
	lcd.draw_big_number (54,0,11);
	lcd.draw_big_number (65,0,8);
	lcd.hor_line (0,84,26,2);
	lcd.string_screen (5,5, "235");
	lcd.string_screen (32,5, "225");
	lcd.string_screen (62,5, "315");
	/*lcd.bin_number (5,0,0x0F);
	lcd.bin_number (5,1,0xF0);
	lcd.draw_char (20,2,'A');
	lcd.string_screen (10,3, "HELLO");
	lcd.string_screen (10,4, "STM32F030K6");
	lcd.string_screen (10,5, "YEAH");
	delay_ms (1000);
	lcd.draw_buffer ();
	delay_ms (1000);
	lcd.draw_char_buffer (25,2,'N');
	lcd.draw_buffer ();
	delay_ms (1000);
	lcd.string_buffer (25,3, "HELLO");
	lcd.draw_buffer ();	
	delay_ms (1000);
	lcd.string_buffer (10,3, "STM32F030K6");
	lcd.hor_line_buffer (10,84,4,1);
	lcd.draw_buffer ();	//
	delay_ms (1000);	
	lcd.string_buffer (5,5, "HIGHER!!!");
	lcd.draw_buffer ();	
	delay_ms (1000);*/
	//lcd.gotoxy (0,0);
	/*delay_ms (1000);
	DMA1_Channel5->CCR |= DMA_CCR_EN;
	
	lcd.draw_pictur (pic1, length);
	
	DMA1_Channel3->CCR |= DMA_CCR_EN;
	delay_ms (1000);
	lcd.draw_pictur (pic1, length);*/
	while (1)
	{
		/*
		for (uint8_t i=0;i<4;++i)
		{
			lcd.gotoxy (0,0);
			DMA1_Channel3->CNDTR = 500;
			DMA1_Channel3->CMAR = (uint32_t) (arr [i]);
			lcd.assert_chip();
			DMA1_Channel3->CCR |= DMA_CCR_EN;
			delay_ms (1000);
		}*/
	}
}


void init_dma_spi_tx ()
{
	RCC->AHBENR |= RCC_AHBENR_DMAEN;
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
	DMA1_Channel3->CPAR = (uint32_t) (&(SPI1->DR));
	DMA1_Channel3->CMAR = (uint32_t) (arr [2]);
	DMA1_Channel3->CNDTR = length;
	DMA1_Channel3->CCR &= ~ (DMA_CCR_MSIZE|DMA_CCR_PSIZE);
	DMA1_Channel3->CCR |= DMA_CCR_MINC|DMA_CCR_TCIE |DMA_CCR_DIR;
	NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

}

void init_dma_mem ()
{
	RCC->AHBENR |= RCC_AHBENR_DMAEN;
	DMA1_Channel5->CPAR = (uint32_t) (pic1);
	DMA1_Channel5->CMAR = (uint32_t) (pic);

	//*(reg)(DMA1_Channel5_BASE+0x0C-1) |= 251;
	//DMA1_Channel5->CNDTR = length;
	DMA1_Channel5->CCR &= ~ (DMA_CCR_MSIZE|DMA_CCR_PSIZE);
	DMA1_Channel5->CCR |= DMA_CCR_MINC|DMA_CCR_TCIE |DMA_CCR_DIR|DMA_CCR_PINC	| DMA_CCR_MEM2MEM; 
	NVIC_EnableIRQ(DMA1_Channel4_5_IRQn);	
}

void pic_shift (uint8_t sh)
{
	for (uint16_t i=0;i< length;++i)buffer[i] = 0;
	for (uint8_t i=sh;i<84;++i)
	{
		buffer[i] = *pic2;
	}
}

