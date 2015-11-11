#include "max6675.h"

#ifdef SOFTSPI
max6675::max6675 (Port p, uint8_t _sck, uint8_t _miso, uint8_t _cs)
	:pin (p)
	{
		sck = _sck;
		miso = _miso;
		cs = _cs;
		//===Settings pins===//
		pin.setOutPin (sck);
		pin.setOutPin (cs);
		pin.setInPin (miso);
		pin.setPin (cs);
		
	}
#else
	max6675 ();
#endif
