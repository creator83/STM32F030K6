#include "device.h" // Device header
#include "buffer.h"
#include "button.h"
#include "tact.h"
#include "segled.h"
#include "adc.h"
#include "qenc.h"
#include "gtimer.h"
#include "pwm.h"
#include "pid.h"
#include "dma.h"


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

Pwm * triacs [2] = {&triac1, &triac2};

//Buttons & Encoder
Button buttonEnc (Gpio::Port::A, 10);
Button button (Gpio::Port::A, 11);


	uint16_t num = 356;
	char heatState [4] = {0, 0x06, 0x36};
	char buf[4]= {0, 0, 0, heatState[2]};
 char off [3] = {0x3F, 0x3F, 0x71};
	Buffer buffer (buf, 3);
 uint16_t result [8]= {0};
 
 Dma adcTransfer (Dma::dmaChannel::ch1);
	
 Pin adcPin (Gpio::Port::B, 11, Gpio::Afmode::AF1);
 Adc thermocouple (Adc::channel::ch8, Adc::resolution::bit12, adcPin);

extern "C"
{
	void SysTick_Handler ();
 void ADC1_IRQHandler ();
 void DMA1_Channel1_IRQHandler ();
}


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

Pid regulator (p, i, d, setTemp.value);

void ADC1_IRQHandler ()
{
 
}

void DMA1_Channel1_IRQHandler ()
{
 
}

void SysTick_Handler()
{
	static struct
	{
		uint16_t adc;
		uint16_t lcd;
  uint16_t beep;
	}counter{0};
	++counter.adc;
	++counter.lcd;
 //encoder.scan ();
 
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
 
	if (counter.adc>100)
	{
  uint16_t temp=0;
		for (uint8_t i=0;i<8;++i)
  {
    temp += result [i];
  }
  temp >>=3;
  currTemp = temp/200;
  uint16_t pidResult = regulator.compute(currTemp);
  triac1.setValue (pidResult);
  triac2.setValue (pidResult);
	}	
	if (counter.lcd>500)
	{
		counter.lcd = 0;
		buffer.parsDec16(num, 3);
	}	
 if (flag.triacs)
 {
  
 }
	else
 {
  
 }
	indicator.value(buf, 4);

}

/*



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
*/
void buttonEncShort ();
void buttonEncLong ();

void buttonShort ();
void buttonLong ();

void initData ();

int main()
{
	beeper.setValue (0);
	beeper.start ();
	//char f=0xFF;
	buffer.setFont(ArraySegChar);
 adcTransfer.setPtrMem ((uint32_t)result);
 adcTransfer.setPtrPeriph((uint32_t)&ADC1->DR);
 adcTransfer.setIncMem (true);
 adcTransfer.setIncPer (false);
 adcTransfer.setDirection (Dma::direction::periph2mem);
 adcTransfer.setLength (8);
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
	

	
*/
	//settings buttons
	button.setShortLimit(10);
	buttonEnc.setShortLimit(10);
	buttonEnc.setshortPressAction(buttonEncShort);
	buttonEnc.setlongPressAction(buttonEncLong);
	button.setshortPressAction(buttonShort);
	button.setlongPressAction(buttonLong);

	button.setLongLimit(1000);
	buttonEnc.setLongLimit(1000);


	uint16_t j=0;
	while (1)
	{
		++j;
	}
}

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
 switch (flag.triacs)
 {
  case 0:
  {
    triac1.stop();
    triac2.stop();
    break;
  }
  case 1:
  {
    triac1.start();
    triac2.stop();
    break;
  }  
  case 2:
  {
    triac2.start();
    triac1.stop();
    break;
  } 
   case 3:
  {
    triac1.start();
    triac2.start();
    break;
  }
 }
}

void buttonEncLong ()
{
	if (!flag.setBeeper)
	{
		flag.setTemp ^= 1;
	}
 if (flag.setTemp)
 {
  encoder.setValue(setTemp.value);
 }
 else
 {
   setTemp.value = encoder.getValue();
 }
}

void buttonShort ()
{
	if (!flag.setTemp||!flag.setBeeper)
	{
		flag.startBeeper ^= 1;
	}
}

void buttonLong ()
{
	if (!flag.setTemp)
	{
		flag.setBeeper ^= 1;
	}
}

