#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "max6675.h"
#include "uart.h"

tact frq;

int main()
{

  uart uart1 (uart::baud9600);
  max6675 sensor;
  
  
  while (1)
  {
		sensor.buffer (sensor.readCelsius());
		uart1.transmit ("==");
		uart1.transmit (sensor.buffer_value[0]);
		uart1.transmit (sensor.buffer_value[1]);
		delay_ms (500);
  }
}
