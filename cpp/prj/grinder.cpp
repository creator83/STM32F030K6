#include "stm32f0xx.h"
#include "Gpio.h"
#include "delay.h"
#include "tact.h"
#include "systimer.h"
#include "segled.h"

tact frq;
Gpio A (Gpio::A);
Gpio B (Gpio::B);

segled indicator (segled::A);

char number [13] = {0x3F ,0x06 , 0x5B , 0x4F , 0x66 , 0x6D , 0x7D, 0x07 , 0x7F , 0x6F ,  0x00, 0x60, 0x6A};
char numberDp [13] = {0xBF , 0x86 , 0xDB , 0xCF , 0xE6 , 0xED , 0xFD , 0x87 , 0xFF , 0xEF , 0x00, 0x60, 0x6A};


void scan_enc ();

const char button = 6 ;
const char enc_button = 1 ;
const char triac = 3;
const char encA = 9 ;
const char encB = 10;

struct encdr
{
	uint8_t state;
	uint16_t count;
}encod;



uint16_t N = 62;

void TIM14_init ();
void TIM3_init ();

struct flags
{
	unsigned led_indicator_delay : 1;
	unsigned off :1;
	unsigned enc_off :1;
}flag;



	struct b_flags
{
	unsigned lmt_sh_press : 6;
	unsigned curr_state   : 1;
	unsigned action_state : 1;
	unsigned count        : 7;
	unsigned sh_press     : 1;
	unsigned l_press      : 1;
	unsigned debouncer    : 1;
}button1, enc_btn;

void btn_action ();
void enc_btn_action ();
extern "C"
{
	void SysTick_Handler ();
	void TIM14_IRQHandler ();
	void TIM17_IRQHandler ();
	void TIM3_IRQHandler ();
	void TIM16_IRQHandler ();
}

   /* */
void SysTick_Handler ()
{
	if (flag.off) ;
	else
	{
	if (flag.led_indicator_delay)flag.led_indicator_delay = 0;
	else
	{
		indicator.digit();
		flag.led_indicator_delay = 1;
	}
	}
	if (!(flag.off||flag.enc_off)) scan_enc ();
}
  
void TIM3_IRQHandler ()
{
	TIM3->SR &= ~TIM_SR_UIF;
	if (button1.sh_press)  btn_action ();
	if (enc_btn.sh_press)enc_btn_action ();
}

void TIM17_IRQHandler ()
{
	TIM17->SR &= ~TIM_SR_UIF;
	flag.enc_off = 1;
	if (N)
	{
		N--;
		indicator.get_buffer (N);
		A.setPin (triac);
	}
	else 
	{
		TIM17->CR1 &= ~TIM_CR1_CEN;
		A.clearPin (triac);	
		indicator.get_buffer (encod.count>>1);
		flag.enc_off = 0;
	}
}

void TIM14_IRQHandler ()
{
	TIM14->SR &= ~TIM_SR_UIF;
//debouncer
	
//scan button
	if (!flag.off)
	{
		if  (!button1.debouncer)
		{
	if (button1.curr_state)
	{
		if (!A.PinState(button)) button1.count++;
		if (A.PinState(button)&&button1.count>2)
		{
			button1.curr_state = 0;
			button1.count = 0;
			button1.sh_press = 1;
		}

	}
	else
	{
		if (!A.PinState(button)) button1.curr_state = 1;
	}
	}
		else button1.count++;
	if (button1.debouncer&&button1.count>5) 
	{
		button1.debouncer=0;
		button1.count = 0;
	}
	}
	
	//scan button encoder
		if  (!enc_btn.debouncer)
		{
		if (enc_btn.curr_state)
	{
		if (!B.PinState(enc_button)) enc_btn.count++;
		if (B.PinState(enc_button)&&enc_btn.count>2)
		{
			enc_btn.curr_state = 0;
			enc_btn.count = 0;
			enc_btn.sh_press = 1;
		}

	}
	else
	{
		if (!B.PinState(enc_button)) enc_btn.curr_state = 1;
	}
	}
		else enc_btn.count++;
	if (enc_btn.debouncer&&enc_btn.count>5) 
	{
		enc_btn.debouncer=0;
		enc_btn.count = 0;
	}
			
}
	

/*
void TIM14_IRQHandler ()
{
	TIM14->SR &= ~TIM_SR_UIF;
	if (button1.action_state)
	{
		if (A.PinState(button))
		{
			button1.action_state = 0;
			return;
		}	
	}
	else
	{
		
	if (button1.curr_state)
	{
		if (!A.PinState(button))
		{
			if (button1.count>100)
			{
				button1.action_state = 1;
				button1.l_press = 1;
				button1.count = 0;
				button1.curr_state = 0;				
			}
			else
			{
				button1.count++;
				return;
			}
		}
		else
		{
			if (button1.count<50)
			{
				button1.sh_press = 1;
				button1.count = 0;
				button1.curr_state = 0;
			}

		}
				
	}
	else
	{
		if (!A.PinState(button)) 
		{
			button1.curr_state = 1;
		}
	}
	
}
	
}
*/
void TIM17_init ();


int main()
{
	encod.count = N << 1;
	indicator.get_buffer (encod.count>>1);
	A.setOutPin (triac);
	A.setInPin (button);
	A.setInPin (encA);
	A.setInPin (encB);
	B.setInPin (enc_button);
	
	systimer sys(systimer::ms, 1);
	NVIC_SetPriority(SysTick_IRQn, 0);
	TIM14_init ();
	TIM17_init ();
	TIM3_init ();
	
  while (1)
  {

  }
}

void TIM14_init ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM14EN ;
	TIM14->PSC = tact::get_frq()*1000 - 1;
	TIM14->ARR = 20;
	TIM14->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM14_IRQn);
	TIM14->CR1 |= TIM_CR1_CEN;
}

void TIM17_init ()
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	TIM17->PSC = tact::get_frq()*1000 - 1;
	TIM17->ARR = 100;
	TIM17->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM17_IRQn);
	NVIC_SetPriority(TIM17_IRQn, 2);
}

void TIM3_init ()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->PSC = tact::get_frq()*1000 - 1;
	TIM3->ARR = 1;
	TIM3->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_SetPriority(TIM3_IRQn, 2);
	TIM3->CR1 |= TIM_CR1_CEN;
	
}

void btn_action()
{
		button1.sh_press = 0;
		enc_btn.debouncer = 1;
		N = encod.count>>1;
		TIM17->CR1 |= TIM_CR1_CEN;
		
}


void enc_btn_action ()
{
	enc_btn.debouncer = 1;
	enc_btn.sh_press = 0;
	flag.off ^= 1;
	indicator.OFF ();
}

void scan_enc ()
{
	uint8_t new_;
	new_ = (1 << A.PinState(encA))|A.PinState(encB);
	switch (encod.state)
	{
		case 2:
		{
			if (new_ == 3) encod.count++;
			if (new_ == 0) encod.count--;
			break;
		}
		case 0:
		{
			if (new_ == 2) encod.count++;
			if (new_ == 1) encod.count--;
			break;
		}
		case 1:
		{
			if (new_ == 0) encod.count++;
			if (new_ == 3) encod.count--;
			break;
		}		
		case 3:
		{
			if (new_ == 1) encod.count++;
			if (new_ == 2) encod.count--;
			break;
		}				
	}
	encod.state = new_;
	indicator.get_buffer (encod.count>>1);
}

