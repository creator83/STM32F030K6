#include "stm32f0xx.h"                  // Device header
#include "gpio.h"

#ifndef ADC_H
#define ADC_H



class Adc
{
	//variables
public:
	enum channel {ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, ch10, ch11, ch12, ch13, ch14, ch15, ch16, ch17};
	enum clockSource {hsi, pclk_2, pclk_4};
	enum mode {scmsw, ccmsw, scmhw, ccmhw};
	enum resolution {bit12, bit10, bit8, bit6};

	
private:
Gpio pin;

public:	
	Adc();
	Adc(Gpio::Port p, uint8_t pin_);
	void settingsPin (Gpio::Port p, uint8_t pin);
	uint16_t getValue ();
	void start ();
	void stop ();
private:
	void calibrate ();
	void setClock (clockSource s);
	void enable ();
	void disable ();
	void config (mode m, resolution r);
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