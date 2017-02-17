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



#ifndef SPI_H
#define SPI_H
/*namespace spiDef
{
//===Defenitions===//
//SCK
 const Gpio::Port sckPort = Gpio::Port::A;
 const Gpio::Afmode sckAf = Gpio::Afmode::AF0;
const uint8_t sckPin = 5;

//MOSI
const Gpio::Port mosiPort = Gpio::Port::A;
const Gpio::Afmode mosiAf = Gpio::Afmode::AF0;
const uint8_t mosiPin = 7;
	
//MISO
const Gpio::Port misoPort = Gpio::Port::A;
const Gpio::Afmode misoAf = Gpio::Afmode::AF0;
const uint8_t misoPin = 6;	
	
}*/

class Spi;

typedef uint16_t(Spi::*PotMemFn)() ;
typedef uint16_t(Spi::*ptr_ex)(uint16_t) ;
typedef void(Spi::*PtrF1)();
typedef void(Spi::*PotMemF)(uint16_t) ;

class Spi
{
//variables
public:
 enum class nSpi {spi1, spi2};
	enum class mode {hardware, software};
	enum class division {div2 , div4 , div8 , div16 , div32 , div64 , div128 , div256};
	enum class role {slave , master};
 enum class cpol {neg, pos};
 enum class cpha {first, second};
	enum class fsize {bit_4=3, bit_5, bit_6, bit_7, bit_8, bit_9, bit_10, bit_11, bit_12, bit_13, bit_14, bit_15, bit_16};

private:
// Pin sck, mosi, miso;
	static SPI_TypeDef * SpiBase [2];
	static PotMemFn ptr_receive[2];
	static PotMemF ptr_transmite[2];
 static ptr_ex ptr_exchange[2];
	static PtrF1 spi_mode [2];
	uint8_t size_;
	uint8_t spi_m;
 uint8_t spiN;

//functions
public:
 //for spi1
 Spi(role r, mode m);
 Spi(role r= role::master);
 // for spi1, spi2
 Spi(nSpi, role r= role::master);

	void hardwareMode ();
	void softwareMode ();

	
 void setCpol (cpol c = cpol::neg);
 void setCpha (cpha c = cpha::first);
 void setFsize (fsize f = fsize::bit_8);
 void setBaudrate (division d);
	void start ();
	void stop ();

	uint8_t & GetSpiMode (){return spi_m;}
	SPI_TypeDef * getSpiPtr (){return SpiBase [spiN];}
	static void setCpol (Spi &, cpol c);
 static void setCpha (Spi &, cpha c);
 static void setBaudrate (Spi &, division d);
 static void setFsize (Spi &, fsize f = fsize::bit_8);


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

