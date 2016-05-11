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
	uint8_t count;
  enum mode {TXmode , RXmode, PWR_DOWN, STANDBY_1, STANDBY_2};
	enum pin_def {IRQ_, CE=2};
private:
	spi spi1;
	Gpio pin;
	intrpt int1;
	static uint8_t self_addr[5] ;
  static uint8_t remote_addr[5];
  uint8_t chan;
	
//functions

public:	

	nrf24l01 ();
  bool startup;
  uint8_t read_data ();
  void set_state (mode st);
  void rx_state ();
  void tx_state ();
  void stanby1_state();
  uint8_t command (uint8_t cmd_);
  uint8_t w_data (uint8_t data_);
  uint8_t w_reg (uint8_t reg , uint8_t val);
  uint8_t w_reg_buf (uint8_t reg , uint8_t * buf, uint8_t count_);
  uint8_t r_reg_buf (uint8_t reg , uint8_t * buf, uint8_t count_);
  uint8_t r_reg (uint8_t reg); 
  bool send_data (uint8_t * buf, uint8_t size);
  bool send_byte (uint8_t data_);
	void w_tx_buffer (uint8_t data_);
  uint8_t receive_byte ();
  uint8_t get_status ();
  void change_bit (uint8_t reg, uint8_t bit, bool state_);
  bool init ();
  uint8_t check_radio ();
private:
	
	
	
};


//inline void nrf24l01::stanby1_state(){pin.clearPin (ce_);}

#endif
