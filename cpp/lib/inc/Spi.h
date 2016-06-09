#include "stm32f0xx.h"                  // Device header
#include "gpio.h"

/*********************************
SPI driver for 

***********************************/
/*

SPI1
A: CS = 4,15; SCK = 5; MOSI = 7; MISO = 6;

B: CS = SCK = 3 MOSI = 5 MISO = 4

SPI2 for stm32f030c8
B: CS = 12 SCK = 13 MOSI = 15 MISO = 14

*/


#ifndef SPI_H
#define SPI_H

class spi;

typedef uint16_t(spi::*PotMemFn)() ;
typedef uint16_t(spi::*ptr_ex)(uint16_t) ;

typedef void(spi::*PotMemF)(uint16_t) ;

class spi
{
//variables
public:
	enum mode {hardware, software};
	enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256};
	enum Role {slave , master};
  enum Cpol {neg, pos};
  enum Cpha {first, second};
	static uint8_t pins_d[2][4];
	enum Size {bit8, bit16};
	enum PORT {A, B, C, D};
	
	enum pin_def {CS, SCK , MISO , MOSI};
	uint8_t port_;
	uint8_t size_;
private:
  Gpio pin;
	static PotMemFn ptr_receive[2];
	static PotMemF ptr_transmite[2];
  static ptr_ex ptr_exchange[2];

//functions
public:
  spi(PORT p, Division div, Cpol cpl = neg, Cpha cph = first, Role r = master, Size s=bit8);
	void Set_CS ();
  void Clear_CS ();
	uint16_t get_data ();
	void put_data (uint16_t data);
  void transmit_8 (uint16_t data);
  void transmit_16 (uint16_t data);
	void transmit (uint16_t data);
	uint16_t receive_8 ();
	uint16_t receive_16 ();
	uint16_t receive ();

	uint16_t exchange_8 (uint16_t data);
	uint16_t exchange_16 (uint16_t data);
	uint16_t exchange (uint16_t data);	


	bool flag_bsy ();
	bool flag_txe ();
	bool flag_rxne ();
	uint8_t flag_ftvl ();
private:
};

inline void spi::put_data (uint16_t data){*(uint8_t *)&(SPI1->DR) = static_cast <uint8_t> (data);}
inline uint16_t spi::get_data (){return SPI1->DR;}
inline bool spi::flag_bsy (){return SPI1->SR&SPI_SR_BSY;}
inline bool spi::flag_txe (){return SPI1->SR&SPI_SR_TXE;}
inline bool spi::flag_rxne (){return SPI1->SR&SPI_SR_RXNE;}
inline uint8_t spi::flag_ftvl (){return SPI1->SR&SPI_SR_FTLVL;}




#endif

