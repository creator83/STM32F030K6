#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"
#include "segled.h"
#include "max6675.h"

tact frq;
segled indicator (segled::A, segled::A);
//Gpio beeper (Gpio::A);
Gpio button (Gpio::B);
Gpio B (Gpio::B);

const uint8_t butt = 5;
const uint8_t beep = 7;

void encoder_init ();
void init_pwm ();
void init_gpio ();

struct flags
{
	unsigned led_indicator_delay : 1;
}flag;

struct button_flags
{
	unsigned butt_state : 1;
	unsigned curr_state : 1;
	unsigned prev_state : 1;
	unsigned count      : 6;
}butt_flag, enc_flag;

struct task_flags
{
	unsigned butt   : 1;
	unsigned beeper : 1;
	unsigned c_beeper : 12;
}t_flag;

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
	if (!t_flag.butt)
	{
		if (!button.PinState(butt)) butt_flag.curr_state = 1;
		else butt_flag.curr_state = 0;
		if (butt_flag.curr_state && butt_flag.prev_state) butt_flag.count++;
		else butt_flag.count = 0;
		if (butt_flag.count>10) t_flag.butt = 1;
		butt_flag.prev_state = butt_flag.curr_state;
	}
	if (t_flag.butt)
	{
		t_flag.c_beeper++;
	}

}


int main()
{
	
	B.setOutPin (4);
	B.setPin (4);
	init_gpio ();
	//init_pwm ();
	//beeper.setOutPin (beep);
	button.setInPin (butt);
	encoder_init ();
	TIM1->CNT = 1040;
	max6675 sensor;
	systimer (systimer::ms, 1);
	//beeper.setPin (7);
	
	
  while (1)
  {
		indicator.get_buffer (sensor.readCelsius());
		//indicator.get_buffer (TIM1->CNT>>2);
		delay_ms (500);
		/*
		if (t_flag.butt) 
		{
			if (t_flag.c_beeper<5000)
			{
				TIM3->CR1 |= TIM_CR1_CEN;
			}
			else
			{
				t_flag.butt = 0;
				t_flag.c_beeper = 0;
				TIM3->CR1 &= ~TIM_CR1_CEN;
			}
		}*/
		//beeper.ChangePinState (beep);
  }
}




void encoder_init ()
{
	//Turn on tact
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//===Settings pins===//
	GPIOA->MODER &= ~(GPIO_MODER_MODER8|GPIO_MODER_MODER9);
	GPIOA->MODER |= GPIO_MODER_MODER8_1|GPIO_MODER_MODER9_1;
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR8_0|GPIO_PUPDR_PUPDR9_0;
	GPIOA->AFR[1] = (2 << 0)|(2 << 4);
	
	//===Settings timer===//
	TIM1->CCMR1 |= TIM_CCMR1_IC1F|TIM_CCMR1_IC2F;
	TIM1->CCMR1 |= TIM_CCMR1_CC1S_0|TIM_CCMR1_CC2S_0;
	TIM1->CCER &=  ~(TIM_CCER_CC1P|TIM_CCER_CC2P);
	TIM1->SMCR |= TIM_SMCR_SMS_0|TIM_SMCR_SMS_1;
	TIM1->CR1 |= TIM_CR1_CEN;
	TIM1->CNT = 0;
}


void init_pwm ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	//TIM3->PSC |= 2;
	//TIM3->ARR |= 10;
	TIM3->CCER |= TIM_CCER_CC2E;
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2M_2;
	TIM3->CCR2 = 5000;
	//TIM3->CR1 |= TIM_CR1_CEN;
	
}
void init_gpio ()
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER7;
	GPIOA->MODER |= GPIO_MODER_MODER7_1;
	GPIOA->AFR[0] |= 1 << 28;
}
