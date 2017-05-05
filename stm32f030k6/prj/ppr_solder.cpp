#include "device.h" // Device header
#include "gtimer.h"
#include "adc.h"
#include "segled.h"
#include "pwm.h"
#include "pid.h"
#include "buffer.h"
#include "systimer.h"
#include "senc.h"
#include "button.h"


extern "C"
{
	void SysTick_Handler ();
}

Tact frq;
//pid value

const double p  = 2.0;
const double i  = 0.3;
const double d  = 0.5;
uint16_t currTemp;
uint16_t pidVal;

struct data
{
  uint16_t value;
  uint16_t lowLimit;
  uint16_t highLimit;
} setTemp{260}, beepVal;

struct
{
	uint16_t blink;
	uint16_t beep;
}interval{500};



struct
{
	unsigned triacs : 3;
	unsigned setTemp  : 1;
	unsigned setBeeper  : 1;
	unsigned startBeeper  : 1;
}flag{0};

Systimer mainloop (Systimer::mode::ms, 1);


Buffer buffer (4);
Pid regulator (p, i, d, setTemp.value);

void SysTick_Handler ()
{
}


Segled indicator (4);

Pin triac1Pin (Gpio::Port::B, 6, Gpio::Afmode::AF0);
Pin triac2Pin (Gpio::Port::B, 7, Gpio::Afmode::AF0);
Pin beeperPin (Gpio::Port::B, 10, Gpio::Afmode::AF1);

/*

Pin adcPin (Gpio::Port::A, 2, Gpio::mux::Analog);
Adc thermocouple (Adc::mode::hardwareTrg, Adc::channel::SE1, Adc::resolution::bit12, adcPin);


//Pwm channels
Pin triac1Pin (Gpio::Port::B, 6, Gpio::mux::Alt2);
Pin triac2Pin (Gpio::Port::B, 7, Gpio::mux::Alt2);
Pin beeperPin (Gpio::Port::B, 10, Gpio::mux::Alt2);
Tpm tpm1 (Tpm::nTpm::TPM_1, Tpm::division::div8);
Tpm tpm0 (Tpm::nTpm::TPM_0, Tpm::division::div8);
Pwm triac1 (tpm1, triac1Pin, Tpm::channel::ch0, Pwm::mode::EdgePwm, Pwm::pulseMode::highPulse);
Pwm triac2 (tpm1, triac2Pin, Tpm::channel::ch1, Pwm::mode::EdgePwm, Pwm::pulseMode::highPulse);
Pwm beeper (tpm0, beeperPin, Tpm::channel::ch1, Pwm::mode::EdgePwm, Pwm::pulseMode::highPulse);


Pwm * triacs [2] = {&triac1, &triac2};


//Buttons & Encoder
Senc encoder (Gpio::Port::A, 3, Gpio::Port::A, 4);
Button buttonEnc (Gpio::Port::A, 5);
Button button (Gpio::Port::A, 6);






void ADC0_IRQHandler ()
{
	uint16_t result = thermocouple.getResult();

	currTemp = result/200;
	uint16_t pidResult = regulator.compute(currTemp);
	for (uint8_t i=0;i<2;++i)
	{
		if (flag.triacs&(1 << i))
		{
			triacs[i]->setValue(pidResult);
		}
	}
}

void SysTick_Handler ()
{
	static struct
	{
		uint16_t beep;
	}counter{0};

	if (flag.setTemp)
	{
		encoder.scan();
		setTemp.value = encoder.getValue();
		buffer.parsDec16(setTemp.value);
		indicator.blink(buffer.getContent(), buffer.getCount(), interval.blink);
		buttonEnc.scanButton();
		buttonEnc.scanAction();
	}
	else if (flag.setBeeper)
	{
		encoder.scan();
		beepVal.value = encoder.getValue();
		interval.beep = beepVal.value;
		buffer.parsDec16(beepVal.value);
		indicator.blink(buffer.getContent(), buffer.getCount(), interval.blink);
		button.scanButton();
		button.scanAction();
	}
	else if (flag.startBeeper)
	{
		counter.beep++;
		if (counter.beep>100)
		{
			counter.beep = 0;
			interval.beep--;
		}
		buffer.parsDec16(interval.beep);
		indicator.value(buffer.getContent(), buffer.getCount());
	}
	else
	{
	//indicate current temperature
	buffer.parsDec16(currTemp);
	indicator.value(buffer.getContent(), buffer.getCount());
	button.scanButton();
	button.scanAction();
	buttonEnc.scanButton();
	buttonEnc.scanAction();
	}
}

void buttonEncShort ();
void buttonEncLong ();

void buttonShort ();
void buttonLong ();

void initData ();
*/
int main()
{
/*	initData();
	thermocouple.calibrate();


	buffer.parsDec16 (1284);

	thermocouple.setHwTrg(Adc::hwTriger::lptmr0);
	thermocouple.setHwAVG(Adc::samples::smpls32);
	thermocouple.interruptEnable();
	thermocouple.setADC();


	//10ms
	adcTrigger.setComp(30000);
	adcTrigger.start();

	//settings buttons
	button.setShortLimit(10);
	buttonEnc.setShortLimit(10);
	buttonEnc.setshortPressAction(buttonEncShort);
	buttonEnc.setlongPressAction(buttonEncLong);
	button.setshortPressAction(buttonShort);
	button.setlongPressAction(buttonLong);

	button.setLongLimit(1000);
	buttonEnc.setLongLimit(1000);
*/
	uint16_t i;

	while (1)
	{
		++i;
	}
}
/*
void initData ()
{
	setTemp.highLimit = 300;
	setTemp.lowLimit = 240;
	beepVal.highLimit = 250;
	beepVal.lowLimit = 0;
	beepVal.value = 60;
}

void buttonEncShort ()
{
	flag.triacs++;
	if (flag.triacs>3) {
		flag.triacs = 0;
	}
	for (uint8_t i=0;i<2;++i)
	{
		if (!(flag.triacs&(1 << i)))
		{
			triacs[i]->setValue(0);
		}
	}
}

void buttonEncLong ()
{
	if (!flag.setBeeper)
	{
		flag.setTemp ^= 1;
	}

}

void buttonShort ()
{
	if (!flag.setTemp)
	{
		flag.startBeeper ^= 1;
	}
	if (flag.startBeeper) beeper.setValue(0x00FF);
	else beeper.setValue(0);
}

void buttonLong ()
{
	if (!flag.setTemp)
	{
		flag.setBeeper ^= 1;
	}
}
*/
