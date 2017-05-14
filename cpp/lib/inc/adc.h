#include "device.h"                  // Device header
#include "pin.h"
#include "dma.h"

#ifndef ADC_H
#define ADC_H



class Adc
{
	//variables
public:
	enum class channel {ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15, ch16, ch17};
	enum class clockSource {hsi, pclk_2, pclk_4};
	enum class mode {scmsw, ccmsw, scmhw, ccmhw, dmasc, dmacc};
	enum class dmaMode {single, continius};
	enum class resolution {bit12, bit10, bit8, bit6};
	
	
private:
	using  ModeFptr = void (Adc::*)();
	Pin * pin;
 Dma * adcDma;
	static Gpio::Port adcPort [18];
	static uint8_t adcPin [18];
	static ModeFptr modeFunction [6];
	uint16_t adcChannel;

public:	
	Adc(Pin & pin_, clockSource);
 Adc (channel, resolution, Pin &, clockSource = clockSource::hsi);
 Adc(mode m, channel ch, resolution r, clockSource = clockSource::hsi);
	void settingsPin (Gpio::Port p, uint8_t pin);
	uint16_t getValue ();
	uint16_t getMesure ();
	void start ();
	void stop ();
	void enableDma ();
private:
	void calibrate ();
	void setClock (clockSource s);
	
	void enable ();
	void disable ();
	void config (mode m, resolution r);
	void setResolution(resolution r);
	void setChannel (channel ch);
	void scmswMode ();
	void ccmswMode ();
	void EocInterrupt (bool state);
	void EosmpInterrupt (bool state);
	void EoseqInterrupt (bool state);
	void clearEoc ();
	void clearEosmp ();
	void clearEoseq ();
	bool flagEoc ();
	bool flagEosmp ();
	bool flagEoseq ();
};

#endif
