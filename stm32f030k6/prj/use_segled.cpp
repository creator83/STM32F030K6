#include "device.h" // Device header
#include "buffer.h"
#include "button.h"
#include "tact.h"
#include "segled.h"
#include "adc.h"
#include "qenc.h"
#include "gtimer.h"
#include "pwm.h"

Tact frq;
Segled indicator (4);
Atimer encDriver;
Qenc encoder (encDriver);

//beeper
Pin beeperPin (Gpio::Port::B, 1, Gpio::Afmode::AF0);
Gtimer beepTimer (Gtimer::nTimer::Timer14, 23999);
Pwm beeper (beepTimer, beeperPin, Gtimer::nChannel::channel1);

//triac1
Pin triac1Pin (Gpio::Port::B, 4, Gpio::Afmode::AF1);
Gtimer triacsTimer (Gtimer::nTimer::Timer3, 23999);
Pwm triac1 (triacsTimer, triac1Pin, Gtimer::nChannel::channel1);

//triac1
Pin triac2Pin (Gpio::Port::B, 5, Gpio::Afmode::AF1);
Pwm triac2 (triacsTimer, triac2Pin, Gtimer::nChannel::channel2);

//Buttons & Encoder
Button buttonEnc (Gpio::Port::A, 10);
Button button (Gpio::Port::A, 11);

	uint16_t num = 356;
	char heatState [3] = {0, 0x06, 0x36};
	char buf[4]= {0, 0, 0, heatState[2]};
	Buffer buffer (buf, 3);
	
/*Pin adcPin (Gpio::Port::B, 11, Gpio::mux::Analog);
	Adc thermocouple (Adc::channel::SE8, Adc::resolution::bit12, adcPin);*/

extern "C"
{
	void SysTick_Handler(void);

}
/*
void HardFault_Handler ()
{
	
}

void LPTimer_IRQHandler (void)
{
	LPTMR0->CSR |= LPTMR_CSR_TCF_MASK;
}*/


void SysTick_Handler()
{
	static struct
	{
		uint16_t adc;
		uint16_t lcd;
	}counter{0};
	++counter.adc;
	++counter.lcd;
	if (counter.adc>100)
	{
		counter.adc = 0;
		//thermocouple.setADC();
	}	
	if (counter.lcd>500)
	{
		counter.lcd = 0;
		buffer.parsDec16(num, 3);
	}	
	
	indicator.value(buf, 4);

}


/*//pid value

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

Pid regulator (p, i, d, setTemp.value);
Buffer buffer (3);
Systimer mainloop (Systimer::mode::ms, 1);


Pin adcPin (Gpio::Port::A, 2, Gpio::mux::Analog);
Adc thermocouple (Adc::mode::hardwareTrg, Adc::channel::SE1, Adc::resolution::bit12, adcPin);
Lptmr adcTrigger (Lptmr::division::div8);

//Pwm channels


Pwm * triacs [2] = {&triac1, &triac2};







extern "C"
{
	void SysTick_Handler ();
	void ADC0_IRQHandler ();
}

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
	beeper.setValue (0);
	beeper.start ();
	//char f=0xFF;
	buffer.setFont(ArraySegChar);
	/*indicator.setSegments (&f);
	indicator.setDigit (1);*/
	//thermocouple.setHwTrg(Adc::hwTriger::lptmr0);
	//thermocouple.interruptEnable();
	SysTick_Config(0xbb80);
	/*thermocouple.setHwAVG(Adc::samples::smpls8);
	while (!(LPTMR0->CSR & LPTMR_CSR_TCF_MASK));
	LPTMR0->CSR &= ~LPTMR_CSR_TEN_MASK;

  Set up LPTMR to use 1kHz LPO with no prescaler as its clock source */
  //LPTMR0->PSR = LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK;

  /* Wait for counter to reach compare value */
  //;

  /* Disable counter and Clear Timer Compare Flag */
  
		/*	
initData();
	

	

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

	uint16_t j=0;
	while (1)
	{
		++j;
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
