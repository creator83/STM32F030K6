#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "mcp3551.h"
#include "uart.h"


int main()
{
  tact frq;
  uart uart1 (uart::baud57600);
  mcp3551 sensor;

  
  while (1)
  {
    uart1.transmit (static_cast <uint8_t>(sensor.getTemp ()));
    //uart1.transmit (sensor.getCode());
    
    //sensor.getCode();
    delay_ms (1000);
  }
}