#include "max6675.h"


max6675::max6675 ()
:spi1(spi::A, spi::div16, spi::neg, spi::falling,spi::master, spi::bit16)
{
	
}

