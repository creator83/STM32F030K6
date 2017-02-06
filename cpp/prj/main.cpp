#include "stm32f0xx.h"
#include "tact.h"



int main()
{
	Tact frq (Tact::srcTact::HSI);
	frq.hseDissable ();
	frq.pllDissable ();
	frq.setAHBdiv (Tact::ahbDivider::div8);
	frq.setAPBdiv (Tact::apbDivider::div4);
	__WFI();

	while (1)
	{
	}
}
