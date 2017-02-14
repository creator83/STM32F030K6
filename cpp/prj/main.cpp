#include "stm32f0xx.h"
#include "tact.h"
#include "spi.h"
#include "gtimer.h"

int main()
{

	Tact frq (Tact::srcTact::HSI);
	Spi spi1;
 Gtimer counter (Gtimer::nTimer::Timer3);
 
	while (1)
	{
		
	}
}
