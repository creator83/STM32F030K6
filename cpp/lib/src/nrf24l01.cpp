#include "nrf24l01.h"

uint8_t Nrf24l01::selfAddress[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};

uint8_t Nrf24l01::remoteAddress[5] = {0xC2, 0xC2, 0xC2, 0xC2, 0xC2};


Nrf24l01::Nrf24l01 (Spi &s)
:cs (nrf24Def::csPort, nrf24Def::csPin, Gpio::Omode::PushPull), ce (nrf24Def::cePort, nrf24Def::cePin, Gpio::Omode::PushPull), irq (nrf24Def::irqPort , nrf24Def::irqPin, Intrpt::sense::Falling_edge)
{
 cs.set ();
 chan = 3;
 mod = &s;
 mod->stop ();
	//settings SPI
	mod->setCpha(Spi::cpha::first);
	mod->setCpol(Spi::cpol::neg);
	mod->setBaudrate(Spi::division::div32);
	mod->setFsize(Spi::fsize::bit_8);
	SPI1->CR1 |= SPI_CR1_SPE;
	
	//checking
  startup = init ();
  
  //settings register
	
	writeRegister(EN_AA, (1 << ENAA_P1)); // ????????? ????????????????? ?????? ?? ?????? 1
  writeRegister(EN_RXADDR, (1 << ERX_P0) | (1 << ERX_P1)); // ????????? ??????? 0 ? 1
  writeRegister(SETUP_AW, SETUP_AW_5BYTES_ADDRESS); // ????? ????? ?????? 5 ????
  writeRegister(SETUP_RETR, SETUP_RETR_UP_TO_2_RETRANSMIT); 
  writeRegister(RF_CH, chan); // ????? ?????????? ??????
  writeRegister(RF_SETUP, RF_SETUP_0DBM); // ????? ???????? 1 ????/? ? ???????? 0dBm
  
  writeRegister(RX_ADDR_P0, remoteAddress, 5); // ????????????? ???????? ?? ????? 0 
  writeRegister(TX_ADDR, remoteAddress, 5);

  writeRegister(RX_ADDR_P1, selfAddress, 5);
  
  writeRegister(RX_PW_P0, 0);
  writeRegister(RX_PW_P1, 32); 
  writeRegister(DYNPD, (1 << DPL_P0) | (1 << DPL_P1)); // ????????? ???????????? ????? ??? ??????? 0 ? 1
  writeRegister(FEATURE, 0x04); // ?????????? ???????????? ????? ?????? ??????
  
  //===Standby-1 mode===//
  delay_ms (15);
  writeRegister (CONFIG, (1 <<PWR_UP | 1 << EN_CRC));
  delay_ms (2);
	
  rxState ();
}

void Nrf24l01::rxState ()
{
  //переключение в RX Mode
  writeRegister (CONFIG, (1 <<PWR_UP | 1 << EN_CRC| 1 << PRIM_RX));
  ce.set();
  delay_us(140);
}

void Nrf24l01::txState ()
{
  ce.clear ();
  writeRegister (CONFIG, (1 <<PWR_UP | 1 << EN_CRC));
  ce.set ();
  delay_us(15);
  ce.clear ();
  delay_us(140);
}

void Nrf24l01::command (uint8_t com)
{
  cs.clear ();
  mod->putData(com);
}

void Nrf24l01::comm (uint8_t com)
{
	cs.clear ();
  mod->putData(com);
  while (mod->flagBsy ())__NOP ();
  cs.set ();
}

uint8_t Nrf24l01::readRegister (uint8_t reg)
{
  command (R_REGISTER|reg);
  while (!mod->flagRxne())__NOP ();
  uint8_t status = mod->getData();
  while (!mod->flagTxe());
  mod->putData (NOP); 
  while (!mod->flagRxne());
  uint8_t reg_val = mod->getData();
  while (mod->flagBsy ());
  cs.set ();
  return reg_val;
}

uint8_t Nrf24l01::readStatus ()
{
	command (NOP);
	while (!mod->flagRxne())__NOP ();
 uint8_t status = mod->getData();
	while (mod->flagBsy ())__NOP ();
 cs.set ();
	return status;
}

void Nrf24l01::writeRegister (uint8_t reg , uint8_t val)
{
 command (W_REGISTER|reg);
 while (!mod->flagTxe());
 mod->putData (val); 
 while (mod->flagBsy ());
 cs.set ();
}

void Nrf24l01::writeRegister (uint8_t reg , uint8_t * val, uint8_t count)
{
  command (W_REGISTER|reg);
  while (count--)
  {
    while (!mod->flagTxe());
    mod->putData (*val++); 
    while (mod->flagBsy ());
    cs.set ();
  }
}

void Nrf24l01::changeBit (uint8_t reg, uint8_t bit, bool state)
{
  uint8_t val = readRegister (reg);
  
  val = val&(~(1 << bit));
  val = val|(state << bit);
  writeRegister (reg, val);
}

void Nrf24l01::sendByte (uint8_t val)
{
  command (W_TX_PAYLOAD);
  while (!mod->flagTxe());
  mod->putData (val); 
  while (mod->flagBsy ());
  cs.set ();
  txState ();
  rxState ();
}

bool Nrf24l01::init ()
{
   for(uint8_t i = 0;i<100;++i) 
   {
   //writeRegister(CONFIG, 
    writeRegister(CONFIG, (/*1 << EN_CRC) | (1 << CRCO) |*/ (1 << PRIM_RX))); // Выключение питания
    if (readRegister(CONFIG) == ((/*1 << EN_CRC) | (1 << CRCO) |*/ (1 << PRIM_RX))) )
                           
    {
      count = i;
      return true;
    }
      // Если после 100 попыток не удалось записать что нужно, то выходим с ошибкой
    delay_ms(1);
   }
  return false;
}

uint8_t Nrf24l01::receiveByte ()
{
  command (R_RX_PAYLOAD);
  while (!mod->flagTxe());
  mod->putData (NOP); 
  while (!mod->flagRxne());
  uint8_t value = mod->getData();
  while (mod->flagBsy ()) __NOP ();
  cs.set ();
  return value;
}



