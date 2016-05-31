#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"
#include "delay.h"
#include "general_timer.h"

#ifndef DS18B20_H
#define DS18B20_H

typedef unsigned int* reg;


const uint8_t SKIP_ROM = 0xCC; // Пропустить индентификацию
const uint8_t CONVERT_T = 0x44; // Измерить температуру
const uint8_t READ_SCRATCHPAD = 0xBE; // Прочитать измеренное

class ds18b20
{
//variables
public:
	enum resolution {bit9, bit10, bit11, bit12};
  enum Port {A , B , C , F=5};
	enum timers {TIM_3, TIM_14, TIM_15, TIM_16, TIM_17};
  
private:
  Gpio pin;
  uint8_t pin_;
//function
public:
  ds18b20(Port p, uint8_t n);
  uint8_t convertTemp ();
private:
  bool find();
	void write_0 ();
	void write_1 ();
  void write_byte (uint8_t data);
  bool read_bit ();
	uint8_t init ();
  uint8_t read_byte ();
  uint16_t GetTemp ();
  uint16_t GetCode (uint8_t size=2);
};

#endif
