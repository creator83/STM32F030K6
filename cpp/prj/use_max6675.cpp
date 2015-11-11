#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "max6675.h"
#include "uart.h"


int main()
{
  tact frq;
  uart uart1 (uart::baud9600);/*
  max6675 sensor (max6675::A , 5 , 4 , 6);*/
  //max6675 sensor;
  
  
  while (1)
  {
		/*
		sensor.readTemp();
		sensor.buffer (sensor.getTemp());
		uart1.transmit ("==");
		for (uint8_t i=0;i<4;++i)
		{
			uart1.transmit (sensor.buff[i]);
		}
    delay_ms (500);*/
  }
}
