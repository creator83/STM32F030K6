#include "nrf24l01.h"

nrf24l01::nrf24l01()
:spi1 (spi::A, spi::div256), pin (Gpio::A) , int1 (intrpt::A, IRQ_, intrpt::Falling_edge)
{
	chan = 3;
  delay_ms (15);
	pin.setOutPin (CE);
  if (init ())
  {
    delay_ms (15);
    change_bit (CONFIG, PWR_UP, 1);
    delay_ms (3);
    startup = true;
  }
  else startup = false;
	
	NVIC_EnableIRQ (EXTI0_1_IRQn);
	
	//===Setup NRF24L01===//
	
	//Delay after power on
	//init();	
}

uint8_t nrf24l01::w_reg (uint8_t reg, uint8_t val)
{
	spi1.Clear_CS();
  spi1.put_data (W_REGISTER|reg);
  while (!spi1.flag_rxne());
  uint8_t status = spi1.get_data();
  while (!spi1.flag_txe());
  spi1.put_data (val); 
  while (!spi1.flag_rxne());
  uint8_t reg_val = spi1.get_data();
  spi1.Set_CS ();
  return reg_val;    
}

uint8_t nrf24l01::r_reg (uint8_t reg)
{
	spi1.Clear_CS();
  spi1.put_data (R_REGISTER|reg);
  while (!spi1.flag_rxne());
  uint8_t status = spi1.get_data();
  while (!spi1.flag_txe());
  spi1.put_data (NOP); 
  while (!spi1.flag_rxne());
  uint8_t reg_val = spi1.get_data();
  spi1.Set_CS ();
  return reg_val;  
}

uint8_t nrf24l01::w_data (uint8_t data_)
{
  spi1.Clear_CS();
  spi1.put_data (W_TX_PAYLOAD);
  while (!spi1.flag_rxne());
  uint8_t status = spi1.get_data();
  spi1.put_data (data_);
  while (spi1.flag_bsy ());
  spi1.Set_CS ();
  return status;
}

uint8_t nrf24l01::command (uint8_t cmd_)
{
  spi1.Clear_CS();
  spi1.put_data (cmd_);
  while (!spi1.flag_rxne());
  uint8_t status = spi1.get_data();
  spi1.Set_CS ();
  return status;
}

uint8_t nrf24l01::get_status ()
{
  spi1.Clear_CS();
  spi1.put_data (NOP);
  while (!spi1.flag_rxne());
  uint8_t status = spi1.get_data();
  spi1.Set_CS ();
  return status; 
}

void nrf24l01::change_bit (uint8_t reg, uint8_t bit, bool state)
{
  uint8_t val = r_reg (reg);
  
  if (state) val = val|(1 << bit);
  else val = val&(~(1 << bit));
  w_reg (reg, val);
}

bool nrf24l01::init ()
{
   for(uint8_t i = 0;i<100;++i) 
   {
    w_reg(CONFIG, /*(1 << EN_CRC) | (1 << CRCO) |*/ (1 << PWR_UP));
    if (r_reg(CONFIG) == (/*(1 << EN_CRC) | (1 << CRCO) |*/ (1 << PWR_UP))) 
    {
      count = i;
      return true;
    }
    delay_ms(1);
   }
  return false;
}

uint8_t nrf24l01::receive_byte ()
{
  spi1.Clear_CS();
  spi1.put_data (R_RX_PAYLOAD);
  while (!spi1.flag_rxne());
  uint8_t status = spi1.get_data();
  while (!spi1.flag_txe());
  spi1.put_data (NOP); 
  while (!spi1.flag_rxne());
  uint8_t value = spi1.get_data();
  spi1.Set_CS ();
  return value;
}

void nrf24l01::rx_state ()
{
   pin.setPin (CE);
 
  change_bit (CONFIG, PRIM_RX, 1);
  pin.setPin (CE);
  delay_us(140);
}

void nrf24l01::w_tx_buffer (uint8_t data_)
{
	spi1.Clear_CS();
  spi1.put_data (W_TX_PAYLOAD);
  while (!spi1.flag_rxne());
  uint8_t status = spi1.get_data();
  while (!spi1.flag_txe());
  spi1.put_data (data_); 
  while (spi1.flag_bsy());
  spi1.Set_CS ();
}




