#include "stm32f0xx.h"
#include "gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"
#include "button.h"
#include "gtimer.h"
#include "pwm.h"

const char b =  15;
const char led =  0;

Tact frq;
Gpio B (Gpio::B);
Button btn1 (Gpio::A, b);
void shortPressac();
void longPressac();



extern "C"
{
	void SysTick_Handler ();
}


void SysTick_Handler ()
{
		
  


int main()
{
	Gtimer timer3 (Gtimer::Timer3, 100, 4800);
	Pwm airHeater (timer3, Gpio::B, 0, Gpio::AF1,  Gtimer::channel3, Pwm::EdgePwm, Pwm::highPulse);
	
	//B.settingPin (led);
	
	btn1.setShortLimit (10);
	btn1.setLongLimit (1000);
	btn1.setshortPressAction (shortPressac);
	btn1.setlongPressAction (longPressac);
	//TIM3->CCR3 = 100;
	airHeater.setValue (3000);
	airHeater.start();
	//Systimer sys(Systimer::ms, 1);
  while (1)
  {

  }
}
