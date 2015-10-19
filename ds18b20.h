#include "stm32f0xx.h"                  // Device header
#include "Gpio.h"
#include "delay.h"

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
  enum Port {A , B , C , F=5};
  
private:
  Gpio pin;
  uint8_t pin_;
  
//function
public:
  ds18b20(Port p, uint8_t n);
  char convertTemp ();
private:
  bool find();
  void write_bit (char bit);
  void write_byte (unsigned char data);
  bool read_bit ();
  uint8_t read_byte ();
  uint16_t GetTemp ();
  
};

#endif