#include "stm32f0xx.h"                  // Device header
#include "gpio.h"

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

#ifndef Spi_H
#define Spi_H


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
  Gpio Cs, Sck, Mosi, Miso;
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

	void set_CS (Gpio::Port p, const uint8_t & pin, Gpio::Afmode af);
	void set_SCK (Gpio::Port p, const uint8_t & pin, Gpio::Afmode af);
	void set_MOSI (Gpio::Port p, const uint8_t & pin, Gpio::Afmode af);
	void set_MISO (Gpio::Port p, const uint8_t & pin, Gpio::Afmode af);

	void set_cpol (Cpol c = neg);
  void set_cpha (Cpha c = first);
  void set_f_size (Fsize f = bit_8);
  void set_baudrate (Division d);
	void start ();
	void stop ();

	mode & GetSpiMode (){return spi_m;}

	static void set_cpol (Spi &, Cpol c);
  static void set_cpha (Spi &, Cpha c);
  static void set_ctar (Spi &, uint8_t c);
  static void set_baudrate (Spi &, Division d);
  static void set_f_size (Spi &, Fsize f = bit_8);


	void assert_Cs (uint8_t p);
  void disassert_Cs (uint8_t p);
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

inline void Spi::put_data (uint16_t data){*(uint8_t *)&(SPI1->DR) = static_cast <uint8_t> (data);}
inline uint16_t Spi::get_data (){return SPI1->DR;}
inline bool Spi::flag_bsy (){return SPI1->SR&SPI_SR_BSY;}
inline bool Spi::flag_txe (){return SPI1->SR&SPI_SR_TXE;}
inline bool Spi::flag_rxne (){return SPI1->SR&SPI_SR_RXNE;}
inline uint8_t Spi::flag_ftvl (){return SPI1->SR&SPI_SR_FTLVL;}




#endif

