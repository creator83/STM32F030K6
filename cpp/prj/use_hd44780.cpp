#include "stm32f0xx.h"
#include "tact.h"
#include "delay.h"
#include "hd44780.h"
#include "qenc.h"
#include "gtimer.h"
#include "buffer.h"

Tact frq;
Hd44780 lcd;
Gtimer timer3 (Gtimer::Timer3);
Gtimer timer14 (Gtimer::Timer14, 100, 4800);


Buffer value;
	
void mainScreen ();

int main()
{
	Qenc encoder (timer3, 100);
	encoder.setValue (25);
	mainScreen ();
	
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
	lcd.setPosition (0, 1);
	lcd.sendString ("HeatGun");
	lcd.setPosition (0, 10);
	lcd.sendString ("F=");
	lcd.setPosition (0, 14);
	lcd.data ('%');
	lcd.setPosition (1, 1);
	lcd.sendString ("Tc=");
	lcd.setPosition (1, 7);
	lcd.data ('C');	
	lcd.setPosition (1, 9);
	lcd.sendString ("Ts=");
	lcd.setPosition (1, 15);
	lcd.data ('C');	
}
