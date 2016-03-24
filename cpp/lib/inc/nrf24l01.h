#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"
#include "Spi.h"
#include "intrpt.h"
#include "nrf24l01registors.h"
#include "delay.h"

#ifndef NRF24L01_H
#define NRF24L01_H




class nrf24l01
{
//variables
public:	

private:
	spi spi1;
	Gpio pin;
	intrpt int1;
	enum pin_def {IRQ_, CE=2};
//functions

public:	

	nrf24l01();
	uint8_t write_register (uint8_t reg, uint8_t data);
	uint8_t read_register (uint8_t reg);
	void sc_bit (uint8_t reg, uint8_t reg_bit, bool state);
	void rx_mode ();
	void tx_mode ();
	void write_data (uint8_t data);
	uint8_t read_data ();
	void send_data(uint8_t data); 

	void init ();
private:
	
	
	
};


#endif
