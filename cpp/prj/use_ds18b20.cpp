#include "stm32f0xx.h"
#include "ds18b20.h"
#include "tact.h"
#include "uart.h"

int main ()
{
  tact frq;
  uart uart1 (uart::baud57600);
  ds18b20 sensor (ds18b20::A , 0);
    
  while (1)
  {
    uart1.transmit (sensor.convertTemp ());
  }
}
