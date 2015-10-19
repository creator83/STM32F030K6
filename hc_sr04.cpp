#include "hc_sr04.h"


hc_sr04::hc_sr04 (Port p , uint8_t trig, uint8_t echo)
:pin (p) , int1 (p, echo, intrpt::RiseFall) , timer (48000 , timer14::prsk)
{
	trig_ = trig;
	echo_ = echo;
	pin.setOutPin (trig);
	NVIC_EnableIRQ(EXTI0_1_IRQn);
}

void hc_sr04::Send_strob()
{
	pin.setPin (trig_);
	delay_us (20);
	pin.clearPin (trig_);
}

void hc_sr04::Get_val ()
{
	Send_strob();
	delay_ms (100);
}

uint16_t hc_sr04::StartStop (uint8_t flag)
{
	if (flag)
	{
		timer.Set_CNT (0);
		timer.Start();
		return 0;
	}
	else
	{
		uint16_t n = timer.Get_CNT();
		timer.Stop();
		return n;
	}
}
