#include "hd44780.h"


Hd44780::Hd44780()
:d4 (hd44780Def::d4port), d5 (hd44780Def::d5port), d6 (hd44780Def::d6port), d7 (hd44780Def::d7port), 
e (hd44780Def::eport), rs (hd44780Def::rsport), rw (hd44780Def::rwport)
{
  d4.settingPin (hd44780Def::d4pin);
  d5.settingPin (hd44780Def::d5pin);
  d6.settingPin (hd44780Def::d6pin);
  d7.settingPin (hd44780Def::d7pin);
  e.settingPin (hd44780Def::epin);
  rs.settingPin (hd44780Def::rspin);
  rw.settingPin (hd44780Def::rwpin);
  d[0] = &d4;
  d[1] = &d5;
  d[2] = &d6;
  d[3] = &d7;
  pins [0] = hd44780Def::d4pin;
  pins [1] = hd44780Def::d5pin;
  pins [2] = hd44780Def::d6pin;
  pins [3] = hd44780Def::d7pin;
  init();
  position=0;
}

void Hd44780::init ()
{
  delay_ms (15);
  tetra (0x03);
  delay_ms (5);
  tetra (0x03);
  delay_us (110);
  tetra (0x03);
  delay_ms (1);
  tetra (0x02);
  delay_ms (1);

  // 2 strings
  initCommand (0x28);
  delay_ms (1);
  //turn on display
  initCommand (0x0C);
  delay_ms (1);
  initCommand (0x06);
  delay_ms (1);
  clear();
}

void Hd44780::tetra (uint8_t t)
{
  eAssert ();
  clearData ();
  setData (t);
  delay_us (2);
  eDisassert ();
}

void Hd44780::command (uint8_t com)
{
  checkBusy ();
  rwDisassert();
  rsDisassert();
  eDisassert();
  tetra (com>>4);
  delay_us(50);
  tetra (com);
}

void Hd44780::initCommand (uint8_t com)
{
  rwDisassert();
  rsDisassert();
  eDisassert();
  tetra (com>>4);
  delay_us(50);
  tetra (com);
}

void Hd44780::data (char b)
{ 
  checkBusy();
  rsAssert ();
  tetra (b>>4);
  delay_us(1);
  tetra (b);
  delay_us(1);
}

void Hd44780::sendString (const char *str)
{
  while (*str) data (*str++);
}

void Hd44780::sendString (uint8_t n, const char *str)
{
  for (uint8_t i=0;i<n;++i) data (*str++);
}

void Hd44780::clear ()
{
  command (clear_dram);
  delay_us (1500);
}

void Hd44780::setPosition (uint8_t col, uint8_t row)
{
  uint8_t addr = second_col*col + row;
  command (addr|set_dram_addr);
}



void Hd44780::newChar (const char *ch, uint8_t addr)
{
  command ((set_cgram_addr+addr*8));
  for (uint8_t i=0;i<8;++i, ch++) data (*ch);
	//send_byte (set_dram_addr, command);
}

void Hd44780::checkBusy ()
{
  d7.settingPin(hd44780Def::d7pin, Gpio::Input);
	d7.settingPP (hd44780Def::d7pin, Gpio::PullUp);
  rwAssert ();
  rsDisassert();
  uint8_t state;
  do
  {
    eAssert();
    delay_us(2);
    state = d7.pinState(hd44780Def::d7pin);
    eDisassert();
    delay_us(1);
    eAssert();
    delay_us(2);
    eDisassert();
  }
  while (state);
  d7.settingPin (hd44780Def::d7pin);
  rwDisassert();
}

void Hd44780::Shift(Shifter s, Direction d, uint8_t val)
{
	command(turn_off_display);
	uint8_t shift_= shift|s|d;
	for (uint8_t i=0;i<val;++i)
	{
		command(shift_);
	}
	command(turn_on_display);
	if (d == Left)
	{
		uint8_t temp = 40 - position;
		if (s > (temp))position = s - temp;
		else position += s;
	}
	else
	{

		if (s > position)
		{
			uint8_t temp = s - position;
			position = 40 - temp;
		}
		else position -= s;
	}

}
void Hd44780::set_shift_position (uint8_t pos)
{
	if (pos<position) Shift(Hd44780::Window, Hd44780::Right, position - pos);
	if (pos > position) Shift(Hd44780::Window, Hd44780::Left, pos - position);
}

uint8_t Hd44780::get_Shift_position ()
{
	return position;
}

void Hd44780::rsAssert ()
{
  rs.setPin(hd44780Def::rspin);
}

void Hd44780::rsDisassert ()
{
  rs.clearPin(hd44780Def::rspin);
}

void Hd44780::eAssert ()
{
  e.setPin(hd44780Def::epin);
}

void Hd44780::eDisassert ()
{
  e.clearPin(hd44780Def::epin);
}

void Hd44780::rwAssert ()
{
  rw.setPin(hd44780Def::rwpin);
}

void Hd44780::rwDisassert ()
{
  rw.clearPin(hd44780Def::rwpin);
}

void Hd44780::clearData ()
{
  d4.clearPin (hd44780Def::d4pin);
  d5.clearPin (hd44780Def::d5pin);
  d6.clearPin (hd44780Def::d6pin);
  d7.clearPin (hd44780Def::d7pin);
}

void Hd44780::setData (uint8_t value)
{
  for (uint8_t i =0;i<4;++i)
  {
    d[i]->SetPinState (pins[i], value & 1 << i);
  }
}
