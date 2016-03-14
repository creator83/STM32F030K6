#include "nrf24l01.h"

nrf24l01::nrf24l01()
:spi1 (spi::A, spi::div256), pin (Gpio::A), int1 (intrpt::A, IRQ_, intrpt::Falling_edge)
{
	pin.setOutPin (CE);
	NVIC_EnableIRQ (EXTI0_1_IRQn);
	
	//===Setup NRF24L01===//
	
	//Delay after power on
	init();	
}

void nrf24l01::write_register (uint8_t reg, uint8_t data)
{
	spi1.Clear_CS();
	
	//command for write registor
	spi1.transmit (W_REGISTER+reg);
	
	//write register
	spi1.transmit (data);
	spi1.Set_CS();	
}

uint8_t nrf24l01::read_register (uint8_t reg)
{
	uint8_t value;	
	
	spi1.Clear_CS ();
	
	//command for read registor
	spi1.transmit (R_REGISTER + reg);
	value = spi1.exchange (NOP);
	spi1.Set_CS ();
	return value;
}

void nrf24l01::sc_bit (uint8_t reg, uint8_t reg_bit, bool state)
{
	uint8_t reg_val = read_register (reg);
	
	if (state) reg_val = reg_val|(1<<reg_bit);
	else reg_val = reg_val|(~(1<<reg_bit));	
	
	spi1.Clear_CS ();
	
	//command for write registor
	spi1.transmit (W_REGISTER+reg);
	
	write_register (reg, reg_val);
}
void nrf24l01::rx_mode ()
{
	//mode standby-1
	pin.clearPin (CE);
	
	//
	sc_bit(CONFIG, PRIM_RX, 1);
	
	pin.setPin (CE);
	delay_us (15);
	delay_us (140);
}
void nrf24l01::tx_mode ()
{
	//mode standby-1
	pin.clearPin (CE);
	
	//
	sc_bit(CONFIG, PRIM_RX, 0);
	
	pin.setPin (CE);
	delay_us (15);
	pin.clearPin (CE);
	delay_us (140);	
}

void nrf24l01::write_data (uint8_t data)
{
	spi1.Clear_CS ();
	spi1.transmit (W_TX_PAYLOAD);
	spi1.transmit (data);
	spi1.Set_CS();
}

uint8_t nrf24l01::read_data ()
{
	uint8_t temp;
	spi1.Clear_CS ();
	spi1.transmit (R_RX_PAYLOAD);
	temp = spi1.exchange (NOP);
	spi1.Set_CS();
	return temp;
}
void nrf24l01::send_data(uint8_t data)
{
	write_data (data);
	tx_mode();
	rx_mode();
}


void nrf24l01::init ()
{
	spi1.Clear_CS ();
	pin.clearPin (CE);
	delay_ms (15);
	
	sc_bit(RX_PW_P0,0,1);
	sc_bit(CONFIG,MASK_MAX_RT,1);
  sc_bit(CONFIG,MASK_TX_DS,2);
  sc_bit(CONFIG,MASK_RX_DR,0);
	
	sc_bit(CONFIG,PWR_UP,1);
  delay_ms(2);
}
