#include "spi.h"

void spi1_init (void)
{
	GPIO_InitTypeDef Gpio_SPI1;
	SPI_InitTypeDef SPI1_user;
	
	//===Settings Pins (SCK, MOSI, MISO)===//
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOA, ENABLE);
	Gpio_SPI1.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	Gpio_SPI1.GPIO_Mode = GPIO_Mode_AF;
	Gpio_SPI1.GPIO_Speed = GPIO_Speed_Level_3;
	Gpio_SPI1.GPIO_OType = GPIO_OType_PP;
	Gpio_SPI1.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init (GPIOA, &Gpio_SPI1);	
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource5,GPIO_AF_0);
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource6,GPIO_AF_0);	
	GPIO_PinAFConfig (GPIOA, GPIO_PinSource7,GPIO_AF_0);
	
	//===Settings Pin CS===//
	
	Gpio_SPI1.GPIO_Pin = GPIO_Pin_4;
	Gpio_SPI1.GPIO_Mode = GPIO_Mode_OUT;
	Gpio_SPI1.GPIO_Speed = GPIO_Speed_Level_1;
	Gpio_SPI1.GPIO_OType = GPIO_OType_PP;
	Gpio_SPI1.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init (GPIOA, &Gpio_SPI1);	
	GPIO_SetBits (GPIOA, GPIO_Pin_4);
	
	//===Settings Spi===//
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_SPI1, ENABLE);
	
	SPI1_user.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI1_user.SPI_Mode = SPI_Mode_Master;
	SPI1_user.SPI_DataSize = SPI_DataSize_8b;
	SPI1_user.SPI_CPOL = SPI_CPOL_Low;
	SPI1_user.SPI_CPHA = SPI_CPHA_2Edge;
	SPI1_user.SPI_NSS = SPI_NSS_Soft;
	SPI1_user.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256 ;
	SPI1_user.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI1_user.SPI_CRCPolynomial = 7;
	
	SPI_Init (SPI1, &SPI1_user);
	SPI_Cmd (SPI1, ENABLE);
}

void tx_byte (uint8_t data)
{
	CS_CLEAR();
	SPI_SendData8 (SPI1, data);
	CS_SET();
}

uint8_t rx_byte (void)
{
	uint8_t data;
	CS_CLEAR();
	data = SPI_ReceiveData8 (SPI1);
	CS_SET();
	return data;
}
