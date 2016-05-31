#include "ds18b20.h"


ds18b20::ds18b20(Port p, uint8_t n)
:pin (p)
{
  pin_ = n;
  pin.setInPin (pin_);
}

uint8_t ds18b20::init ()
{
	if (!pin.PinState (pin_)) return 1;
	pin.setOutPin (pin_);
	pin.clearPin (pin_);
	delay_us (500);
	pin.setInPin (pin_);
	delay_us (60);
	if (pin.PinState (pin_)) return 2;
	delay_us (400);
	if (!pin.PinState (pin_)) return 3;
	return 0;
}

bool ds18b20::find()
{
  pin.PuPd (pin_ , Gpio::PullDown);
  delay_us (485);
  pin.PuPd (pin_ , Gpio::NoPP);
  delay_us (65);
  if (pin.PinState (pin_))
  {
    delay_us (420);
    return true;
  }
  else 
  {
    delay_us (420);
    return false;
  }
}

void ds18b20::write_0 ()
{
	pin.setOutPin (pin_);
	pin.clearPin (pin_);
	delay_us (60);
	pin.setInPin (pin_);
	delay_us (5);
}

void ds18b20::write_1 ()
{
	pin.setOutPin (pin_);
	pin.clearPin (pin_);
	delay_us (5);
	pin.setInPin (pin_);
	delay_us (55);
}
void ds18b20::write_byte (uint8_t data)
{
  for (char i = 0;i<8;++i)
  {
    if (data & (1 << i)) write_1 ();
    else write_0 ();
  }
}

bool ds18b20::read_bit ()
{
  pin.setOutPin (pin_);
	pin.clearPin (pin_);
	delay_us (5);
	pin.setInPin (pin_);
	delay_us (15);
	/*delay_us (30);
	return pin.PinState (pin_);*/
	if (pin.PinState (pin_))
	{
		delay_us (30);
		return 1;
	}
	else 
	{
		delay_us (30);
		return 0;
	}
}

uint8_t ds18b20::read_byte ()
{
  uint8_t data = 0;
  for (uint8_t i = 0;i<8;++i)
  {
    data |= read_bit () << i;
  }
  return data;
}

uint16_t ds18b20::GetTemp ()
{
  uint16_t data;
  if (find ())
  {
    write_byte (SKIP_ROM);
    write_byte (CONVERT_T);
    delay_ms (750);
    find ();
    write_byte (SKIP_ROM);
    write_byte (READ_SCRATCHPAD); 
    data = read_byte();
    data |= (read_byte() << 8);
    return data;
  }
  else return 0;
}

uint16_t ds18b20::GetCode (uint8_t size)
{write_byte (SKIP_ROM);
    write_byte (CONVERT_T);
    delay_ms (750);
	uint16_t data;
	if (!init ())
	{
		write_byte (SKIP_ROM);
    write_byte (CONVERT_T);
    delay_ms (750);
		if (!init ())
		{
			write_byte (SKIP_ROM);
			write_byte (READ_SCRATCHPAD); 
			data = read_byte();
			data |= (read_byte() << 8);
			return data;
		}
	}
	return 0;
}

uint8_t ds18b20::convertTemp ()
{
  uint16_t data = GetTemp ();
  data >>= 4;
	data &= 0x7F;
  return data;
}
