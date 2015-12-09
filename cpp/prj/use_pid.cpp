#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "segled.h"
#include "systimer.h"
#include "max6675.h"
#include "pid.h"

tact frq;
segled indicator (segled::A, segled::A);

/*! \brief P, I and D parameter values
 *
 * The K_P, K_I and K_D values (P, I and D gains)
 * need to be modified to adapt to the application at hand
 */
//! \xrefitem todo "Todo" "Todo list"
#define K_P     1.00
//! \xrefitem todo "Todo" "Todo list"
#define K_I     0.00
//! \xrefitem todo "Todo" "Todo list"
#define K_D     0.00

uint8_t stat;

/*! \brief Flags for status information
 */
struct GLOBAL_FLAGS {
  //! True when PID control loop should run one time
  uint8_t pidTimer:1;
  uint8_t dummy:7;
} gFlags = {0, 0};

//! Parameters for regulator
struct PID_DATA pidData;

struct task
{
	unsigned counter :12;
	unsigned flag :1;
}pid;

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;



extern "C"
{
	void SysTick_Handler ();
}


void SysTick_Handler ()
{
		

	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
		if (pid.counter>400)
	{
		pid.flag = 1;
		pid.counter = 0;
	}
	else pid.counter++;
	
/*	
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}*/

}

void init_timer ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC |= 480-1;
	TIM3->ARR |= 10;
	TIM3->CCER |= TIM_CCER_CC3E;
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2;
	TIM3->CR1 |= TIM_CR1_CEN;
}


int main()
{
	int16_t referenceValue, measurementValue, inputValue;
	referenceValue = 30;
	pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);
  systimer (systimer::ms, 1);
	max6675 sensor;
	init_timer ();
	TIM3->CCR3 = 58980;
	
  while (1)
  {
	/*indicator.get_buffer (sensor.readCelsius());
		delay_ms (500);*/
				if (pid.flag)
		{
			measurementValue = sensor.readCelsius();
			inputValue = pid_Controller(referenceValue, measurementValue, &pidData);
			indicator.get_buffer (inputValue);	
			pid.flag = 0;
		}
		/*if (button.short_press)*/
		{
			// foo();
			//button.short_press = 0;
		}
  }
}
