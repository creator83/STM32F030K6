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

#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
#define VDD_CALIB ((uint16_t) (330))
#define VDD_APPLI ((uint16_t) (300))

Tact frq;
Segled indicator (4);
Atimer encDriver;
Qenc encoder (encDriver, 10);

//beeper
Pin beeperPin (Gpio::Port::B, 1, Gpio::Afmode::AF0);
Gtimer beepTimer (Gtimer::nTimer::Timer14, 47999);
//Pwm beeper (beepTimer, beeperPin, Gtimer::nChannel::channel1, Pwm::mode::EdgePwm, Pwm::pulseMode::lowPulse);

//triac1
Pin triac1Pin (Gpio::Port::B, 4, Gpio::Afmode::AF1);
Gtimer triacsTimer (Gtimer::nTimer::Timer3, 47909);
Pwm triac1 (triacsTimer, triac1Pin, Gtimer::nChannel::channel1);

//triac1
Pin triac2Pin (Gpio::Port::B, 5, Gpio::Afmode::AF1);
Pwm triac2 (triacsTimer, triac2Pin, Gtimer::nChannel::channel2);

Pwm * triacs [2] = {&triac1, &triac2};

//Buttons & Encoder
Button buttonEnc (Gpio::Port::A, 10);
Button button (Gpio::Port::A, 11);


	uint16_t num = 0;
	char heatState [4] = {0, 0x06, 0x36};
	char buf[4]= {0, 0, 0, heatState[2]};
 char off [3] = {0x3F, 0x3F, 0x71};
	Buffer buffer (buf, 3);
 uint16_t result [8]= {0};
 uint16_t temperature;
 
 Dma adcTransfer (Dma::dmaChannel::ch1);
	
 Pin adcPin (Gpio::Port::B, 0, Gpio::Mode::Analog);

	//uint16_t res;
extern "C"
{
	void SysTick_Handler ();
 void ADC1_IRQHandler ();
 void DMA1_Channel1_IRQHandler ();
	void TIM14_IRQHandler ();
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
} setTemp{260}, beepVal{0};

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

void TIM14_IRQHandler ()
{
	TIM14->SR &= ~(TIM_SR_UIF|TIM_SR_CC1IF);
	beeperPin.clear();
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
	button.scanButton();
	button.scanAction();
	buttonEnc.scanButton();
	buttonEnc.scanAction();
	//encoder.scan ();
	if (flag.triacs)
	{
		if (counter.lcd>50)
		{
			counter.lcd = 0;
			buffer.parsDec16(num, 3);
		}	
		if (counter.adc>100)
		{
			temperature=0;
			for (uint8_t i=0;i<8;++i)
			{
				temperature += result [i];
			}
			temperature >>=3;
			temperature /=11;

			uint16_t pidResult = regulator.compute(currTemp);
			triac1.setValue (pidResult);
			triac2.setValue (pidResult);
		}	
	}


	if (flag.setTemp)
	{
		
		encoder.scan();
		num = encoder.getValue();
		buffer.parsDec16(num, 3);
		indicator.blink(buf, 4, 300);
	}
	else if (flag.setBeeper)
	{
		encoder.scan();
		num = encoder.getValue();
		buffer.parsDec16(num, 3);
		indicator.blink(buf, 4, 300);
	}
	else if (flag.startBeeper)
	{

	}
	else
	{
		if (flag.triacs)
		{
			num = temperature;
		}
		else
		{
			buf [0]= 0x3F;
			buf [1]= 0x71;
			buf [2]= 0x71;
			buf [3]= 0;
		}
		indicator.value(buf,4);
	}

}

void buttonEncShort ();
void buttonEncLong ();

void buttonShort ();
void buttonLong ();

void initData ();
void adcInit ();

int main()
{
	//beepTimer.setOneShot (true);
	//beeper.setPeriod (2000);
	//beeper.setValue (1900);
	//TIM14->DIER |= TIM_DIER_CC1IE|TIM_SR_UIF ;
	//NVIC_EnableIRQ (TIM14_IRQn);
	//beeper.start ();
	//char f=0xFF;
	buffer.setFont(ArraySegChar);

	Adc thermocouple (Adc::channel::ch8, Adc::resolution::bit12, adcPin);
	/*ADC1->CHSELR = ADC_CHSELR_CHSEL16;
	ADC->CCR |= ADC_CCR_TSEN|ADC_CCR_VREFEN;
	ADC1->CR |= ADC_CR_ADSTART;
	while ((ADC1->ISR & ADC_ISR_EOC) == 0);
	
	uint16_t dt = ADC1->DR ;
	uint16_t V = (dt*33)/4095;
	
  temperature = ((14-V)*1000)/43;
	temperature += 30;
	*/	
	//RCC->AHBENR |= RCC_AHBENR_DMA1EN; 
	/*ADC1->CFGR1 |= ADC_CFGR1_DMAEN| ADC_CFGR1_DMACFG|ADC_CFGR1_CONT; 
DMA1_Channel1->CPAR = (uint32_t) (&(ADC1->DR)); 
DMA1_Channel1->CMAR = ((uint32_t)result); 
DMA1_Channel1->CNDTR = 8;
DMA1_Channel1->CCR |=  DMA_CCR_MINC | DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0
| DMA_CCR_TEIE | DMA_CCR_CIRC; 
DMA1_Channel1->CCR |= DMA_CCR_EN; 
	ADC1->CR |= ADC_CR_ADSTART;*/
	thermocouple.enableDma();
	adcTransfer.setPtrMem ((uint32_t)result);
	adcTransfer.setPtrPeriph((uint32_t)&ADC1->DR);
	adcTransfer.setIncMem (true);
	adcTransfer.setIncPer (false);
	adcTransfer.setCirc (true);
	adcTransfer.setSize (Dma::size::bit16, Dma::size::bit16);
	adcTransfer.setDirection (Dma::direction::periph2mem);
	adcTransfer.setLength (8);
	adcTransfer.start ();
	thermocouple.start ();
	
	/*indicator.setSegments (&f);
	indicator.setDigit (1);*/
	//thermocouple.setHwTrg(Adc::hwTriger::lptmr0);
	//thermocouple.interruptEnable();
	//RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
	//adcInit ();
		
		buf [0]= 0x3F;
		buf [1]= 0x71;
		buf [2]= 0x71;
		buf [3]= 0;
	initData();
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

	

	
*/
	
	//settings buttons
	button.setShortLimit(3);
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

void adcInit ()
{

	//cal
	if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
{
ADC1->CR &= (uint32_t)(~ADC_CR_ADEN); /* (2) */
}
ADC1->CR |= ADC_CR_ADCAL; /* (3) */
while ((ADC1->CR & ADC_CR_ADCAL) != 0) ;
	//enable
	ADC1->CR |= ADC_CR_ADEN; /* (1) */
while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (2) */
{
/* For robust implementation, add here time-out management */
}

//setings
ADC1->CHSELR = ADC_CHSELR_CHSEL8; /* (2) */
ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (3) */
ADC->CCR |= ADC_CCR_VREFEN; /* (4) */
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
		buf [0]= 0x3F;
		buf [1]= 0x71;
		buf [2]= 0x71;
		buf [3]= 0;
    break;
  }
  case 1:
  {
    triac1.start();
    triac2.stop();
		buf [3] = 0x06;
    break;
  }  
  case 2:
  {
    triac2.start();
    triac1.stop();
		buf [3] = 0x30;
    break;
  } 
   case 3:
  {
    triac1.start();
    triac2.start();
		buf [3] = 0x36;
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
		num = setTemp.value;
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
	 if (flag.setBeeper)
 {
		encoder.setValue(beepVal.value);
		num = beepVal.value;
 }
 else
 {
	 beepVal.value = encoder.getValue();
 }
}

