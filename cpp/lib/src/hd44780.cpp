#include "hd44780.h"


Hd44780::Hd44780()
:d4 (hd44780Def::d4port, hd44780Def::d4pin, Gpio::PushPull),
d5 (hd44780Def::d5port, hd44780Def::d5pin, Gpio::PushPull), 
d6 (hd44780Def::d6port, hd44780Def::d6pin, Gpio::PushPull), 
d7 (hd44780Def::d7port, hd44780Def::d7pin, Gpio::PushPull), 
e (hd44780Def::eport, hd44780Def::epin, Gpio::PushPull), 
rs (hd44780Def::rsport, hd44780Def::rspin, Gpio::PushPull), 
rw (hd44780Def::rwport, hd44780Def::rwpin, Gpio::PushPull)
{
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
  d7.setInputMode (Gpio::PullUp);
  rwAssert ();
  rsDisassert();
  uint8_t state;
  do
  {
    eAssert();
    delay_us(2);
    state = d7.state();
    eDisassert();
    delay_us(1);
    eAssert();
    delay_us(2);
    eDisassert();
  }
  while (state);
  d7.setOutputMode ();
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
  rs.set();
}

void Hd44780::rsDisassert ()
{
  rs.clear();
}

void Hd44780::eAssert ()
{
  e.set();
}

void Hd44780::eDisassert ()
{
  e.clear();
}

void Hd44780::rwAssert ()
{
  rw.set();
}

void Hd44780::rwDisassert ()
{
  rw.clear();
}

void Hd44780::clearData ()
{
  d4.clear();
  d5.clear();
  d6.clear();
  d7.clear();
}

void Hd44780::setData (uint8_t value)
{
  for (uint8_t i =0;i<4;++i)
  {
		if (value & 1 << i)  d[i]->set();
    else d[i]->clear();
  }
}
