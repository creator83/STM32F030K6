#include "systimer.h"


systimer::systimer(mode m, uint16_t val)
{
	switch (static_cast <uint8_t> (m))
	{
		case 0: 
			SysTick_Config (Tact::get_frq()*val);
		break;
		case 1:
			SysTick_Config (Tact::get_frq()*1000*val);
		break;
		case 2:
			SysTick_Config (Tact::get_frq()*1000000*val);
		break;	
	}
}

