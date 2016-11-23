#include "stm32f0xx.h"
#include "tact.h"
#include "delay.h"
#include "hd44780.h"
#include "qenc.h"
#include "gtimer.h"
#include "atimer.h"
#include "buffer.h"
#include "button.h"
#include "pwm.h"
#include "systimer.h"

extern "C"
{
	void SysTick_Handler (void);
}



const uint8_t buttEncPin = 0;
const uint8_t heaterPin = 0;
const uint16_t TsetVal=250;
const uint16_t TcurrVal=0;
const uint16_t speedVal=60;
uint16_t adcValue [8] = {0};

const char cursorChar[8] =
{ 
0x18,
0x1C,
0x1E,
0x1F,
0x1F,
0x1E,
0x1C,
0x18,
};

const char celsiusChar[8] =
{ 
0x18,
0x18,
0x00,
0x06,
0x09,
0x08,
0x09,
0x06,
};

Tact frq;
Hd44780 lcd;
Gtimer timer3 (Gtimer::Timer3);
Gtimer timer14 (Gtimer::Timer14, 100, 4800);
Atimer timer1 (60,100);
Pwm heater (timer14, Gpio::A, heaterPin, Gpio::AF1, Gtimer::channel2, Pwm::EdgePwm, Pwm::highPulse);
Pwm fun (timer1, Gpio::A, heaterPin, Gpio::AF1, Gtimer::channel2, Pwm::EdgePwm, Pwm::highPulse);
Pwm beeper (timer1, Gpio::A, heaterPin, Gpio::AF1, Gtimer::channel1, Pwm::EdgePwm, Pwm::highPulse);

Button buttonEncoder (Gpio::A, buttEncPin);
Buffer value;

typedef void (*PtrF)();

struct flags
{
	unsigned encLongPress : 1;
	unsigned encShortPress : 2;
	unsigned encReady : 1;
	unsigned screens :1;
}flag;

struct position
{
	uint8_t row;
	uint8_t coloumn;
}speedCursor, tempCursor, pCursor, iCursor, dCursor;

struct data
{
	uint16_t value;
	position pos;	
}speed, temp, pVal, iVal, dVal;

position * ScreenCursor [2][3] = {
{&speedCursor, &tempCursor}, 
{&pCursor, &iCursor, &dCursor}
};

enum newChar {celsius, cursor};


data * mainScreenVal [2] [3]= {
{&speed, &temp},
{&pVal, &iVal, &dVal}
};

void mainScreen ();
void pidScreen ();
void changeScreen ();
void getMainScreen ();
void getPidScreen ();
PtrF screenF [2] = {&getMainScreen, &getPidScreen};

void changeLpFlag ();
void changeSpFlag ();

void SysTick_Handler (void)
{
	buttonEncoder.scanButton ();
	if (!flag.encLongPress)
	{
		screenF [flag.encShortPress]();
	}
	else
	{
		lcd.setPosition (ScreenCursor[flag.screens][flag.encShortPress]->row, ScreenCursor[flag.screens][flag.encShortPress]->coloumn);
		lcd.data (cursor);
	}
}



int main()
{
	Qenc encoder (timer3, 100);
	encoder.setValue (speed.value);
	encoder.stop ();
	mainScreen ();
	pidScreen ();
	buttonEncoder.setLongLimit (1500);
	buttonEncoder.setlongPressAction (changeLpFlag);
	Systimer sys (Systimer::ms, 1);
	
	while (1)
	{
		value.pars (encoder.getValue());
		lcd.setPosition (0, 12);
		lcd.sendString (value.getContent());
		delay_ms (1);
		
	}
}


void mainScreen ()
{
	lcd.newChar (celsiusChar, celsius);
	lcd.newChar (cursorChar, cursor);
	lcd.setPosition (0, 1);
	lcd.sendString ("HeatGun");
	lcd.setPosition (0, 10);
	lcd.sendString ("F=");
	lcd.setPosition (0, 14);
	lcd.data ('%');
	lcd.setPosition (1, 1);
	lcd.sendString ("Tc=");
	lcd.setPosition (1, 7);
	lcd.data (0);	
	lcd.setPosition (1, 9);
	lcd.sendString ("Ts=");
	lcd.setPosition (1, 15);
	lcd.data (0);	
	
	speedCursor.row = 0;
	speedCursor.coloumn = 9;
	tempCursor.row = 1;
	tempCursor.coloumn = 8;
}

void pidScreen ()
{
	lcd.setPosition (0, 16);
	lcd.sendString ("P=");
	lcd.setPosition (0, 20);
	lcd.data ('.');
	lcd.setPosition (0, 22);
	lcd.sendString ("I=");	
	lcd.setPosition (0, 26);
	lcd.data ('.');
	lcd.setPosition (0, 28);
	lcd.sendString ("D=");	
	lcd.setPosition (0, 30);
	lcd.data ('.');
}

void getMainScreen ()
{
	lcd.command (clear_counter);
}

void getPidScreen ()
{
	lcd.Shift (Hd44780::Window, Hd44780::Left, 16);
}

void changeLpFlag ()
{
	if (flag.encLongPress) 
	{
		flag.encLongPress = 0;
		lcd.setPosition (ScreenCursor[flag.screens][flag.encShortPress]->row, ScreenCursor[flag.screens][flag.encShortPress]->coloumn);
		lcd.data (' ');
	}
	else flag.encLongPress = 1;
}

void changeSpFlag ()
{
	if (!flag.encLongPress)
	{
		if (flag.encShortPress) 
		{
			flag.encShortPress = 0;
			flag.screens = 0;
		}
		else 
		{
				flag.encShortPress = 1;
				flag.screens = 1;
		}
	}
	
	else if (flag.encLongPress&&flag.screens)//screenPid
	{
		lcd.setPosition (ScreenCursor[flag.screens][flag.encShortPress]->row, ScreenCursor[flag.screens][flag.encShortPress]->coloumn);
		lcd.data (' ');
		flag.encShortPress++;
		if (flag.encShortPress>2) flag.encShortPress = 0;
	}
	else if (flag.encLongPress&&flag.screens) //mainScreen
	{
		lcd.setPosition (ScreenCursor[flag.screens][flag.encShortPress]->row, ScreenCursor[flag.screens][flag.encShortPress]->coloumn);
		lcd.data (' ');
		if (flag.encShortPress) flag.encShortPress = 0;
		else flag.encShortPress = 1;
	}
}
	



