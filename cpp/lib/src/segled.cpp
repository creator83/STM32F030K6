#include "segled.h"

char segled::number [11] = {0x7B , 0x0A , 0xB3 , 0x9F , 0xCA , 0xD9 , 0xF9 , 0x0B , 0xFB , 0xDB , 0x00};
char pins[4] = {segled::first, segled::second, segled::third, segled::fourth};

segled::segled (Port seg, Port dig)
:pin_segment (seg), pin_digit (dig), timer (1, timer14::ms)
{
	//===Settings segment pins===//
	pin_segment.setOutPin (a);
	pin_segment.setOutPin (b);	
	pin_segment.setOutPin (c);
	pin_segment.setOutPin (d);		
	pin_segment.setOutPin (e);
	pin_segment.setOutPin (f);	
	pin_segment.setOutPin (g);
	pin_segment.setOutPin (dp);		
	
	//===Settings digit pins===//
	pin_digit.setOutPin (first);
	pin_digit.setOutPin (second);	
	pin_digit.setOutPin (third);
	pin_digit.setOutPin (fourth);		
	
	//===Settings timer===//
	timer.interrupt (timer14::Compare);
	timer.Start();
}

void segled::OFF ()
{
	pin_digit.clearPin (first);
	pin_digit.clearPin (second);	
	pin_digit.clearPin (third);
	pin_digit.clearPin (fourth);		
}

void segled::frame (uint8_t dig)
{
	pin_digit.clearPin (first);
	pin_digit.clearPin (second);
	pin_digit.clearPin (third);
	pin_digit.clearPin (fourth);
	pin_segment.setValPort (0);
	pin_digit.setPin (pins [dig]);
	pin_segment.setValPort (number[buffer[dig]]);
}

void segled::digit ()
{
	static uint8_t i=0;
	TIM14->SR &= ~TIM_SR_UIF;
	if (flag) flag = false;
		else
	{
		frame (i);
		flag = 1;
		++i;
	}
	if (i>=n)i=0;
}

void TIM14_IRQHandler(segled &a)
{
		void OFF ();
}
