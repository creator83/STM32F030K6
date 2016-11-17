#include "stm32f0xx.h"                  // Device header
#include "pin.h"


/*********************************
Spi driver for 
***********************************/
/*

Spi1
AF0
A: CS = 4,15; SCK = 5; MOSI = 7; MISO = 6;

B: CS = SCK = 3 MOSI = 5 MISO = 4

Spi2 for stm32f030c8
B: CS = 12 SCK = 13 MOSI = 15 MISO = 14

*/

namespace spiDef
{
//===Defenitions===//
//SCK
const Gpio::Port sckPort = Gpio::A;
const Gpio::Afmode sckAf = Gpio::AF0;
const uint8_t sckPin = 5;

//MOSI
const Gpio::Port mosiPort = Gpio::A;
const Gpio::Afmode mosiAf = Gpio::AF0;
const uint8_t mosiPin = 7;
	
//MISO
const Gpio::Port misoPort = Gpio::A;
const Gpio::Afmode misoAf = Gpio::AF0;
const uint8_t misoPin = 6;	
	
}

#ifndef SPI_H
#define SPI_H


class Spi;

typedef uint16_t(Spi::*PotMemFn)() ;
typedef uint16_t(Spi::*ptr_ex)(uint16_t) ;
typedef void(Spi::*PtrF1)();
typedef void(Spi::*PotMemF)(uint16_t) ;

class Spi
{
//variables
public:
	enum mode {hardware, software};
	enum Division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256};
	enum Role {slave , master};
  enum Cpol {neg, pos};
  enum Cpha {first, second};
	enum Fsize {bit_4=3, bit_5, bit_6, bit_7, bit_8, bit_9, bit_10, bit_11, bit_12, bit_13, bit_14, bit_15, bit_16};

private:
  Pin sck, mosi, miso;
	static SPI_TypeDef * SpiBase [2];
	static PotMemFn ptr_receive[2];
	static PotMemF ptr_transmite[2];
  static ptr_ex ptr_exchange[2];
	static PtrF1 spi_mode [2];
	uint8_t size_;
	mode spi_m;

//functions
public:
  Spi(Role r, mode m);

	void hardwareMode ();
	void softwareMode ();

	
	void setCpol (Cpol c = neg);
  void setCpha (Cpha c = first);
  void setFsize (Fsize f = bit_8);
  void setBaudrate (Division d);
	void start ();
	void stop ();

	mode & GetSpiMode (){return spi_m;}
	//SPI_TypeDef * (){return spi_m;}
	static void setCpol (Spi &, Cpol c);
  static void setCpha (Spi &, Cpha c);
  static void setBaudrate (Spi &, Division d);
  static void setFsize (Spi &, Fsize f = bit_8);


	void assert_Cs (uint8_t p);
  void disassert_Cs (uint8_t p);
	uint16_t getData ();
	void putData (uint16_t data);
  void transmit_8 (uint16_t data);
  void transmit_16 (uint16_t data);
	void transmit (uint16_t data);
	uint16_t receive_8 ();
	uint16_t receive_16 ();
	uint16_t receive ();

	uint16_t exchange_8 (uint16_t data);
	uint16_t exchange_16 (uint16_t data);
	uint16_t exchange (uint16_t data);	


	bool flagBsy ();
	bool flagTxe ();
	bool flagRxne ();
	uint8_t flagFtvl ();
private:
};

inline void Spi::putData (uint16_t data){*(uint8_t *)&(SPI1->DR) = static_cast <uint8_t> (data);}
inline uint16_t Spi::getData (){return SPI1->DR;}
inline bool Spi::flagBsy (){return SPI1->SR&SPI_SR_BSY;}
inline bool Spi::flagTxe (){return SPI1->SR&SPI_SR_TXE;}
inline bool Spi::flagRxne (){return SPI1->SR&SPI_SR_RXNE;}
inline uint8_t Spi::flagFtvl (){return SPI1->SR&SPI_SR_FTLVL;}




#endif

