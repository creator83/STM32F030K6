#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "max6675.h"
#include "uart.h"


int main()
{
  tact frq;
  uart uart1 (uart::baud9600);
  max6675 sensor (max6675::A , 0 , 1 , 2);
  //max6675 sensor;
  
  
  while (1)
  {
    uart1.transmit (sensor.getTemp());
    delay_ms (1000);
  }
}