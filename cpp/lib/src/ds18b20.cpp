#include "ds18b20.h"


ds18b20::ds18b20(Port p, uint8_t n)
:pin (p)
{
  pin_ = n;
  pin.setInPin (pin_);
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

void ds18b20::write_bit (char bit)
{
  pin.PuPd (pin_ , Gpio::PullDown);
  delay_us (2);
  if (bit) pin.PuPd (pin_ , Gpio::NoPP);
  delay_us (65);
  pin.PuPd (pin_ , Gpio::NoPP);
}

void ds18b20::write_byte (unsigned char data)
{
  for (char i = 0;i<8;++i)
  {
    if (data& (1 << i)) write_bit (1);
    else write_bit (0);
  }
}

bool ds18b20::read_bit ()
{
  bool bit;
  pin.PuPd (pin_ , Gpio::PullDown);
  delay_us (2);
  pin.PuPd (pin_ , Gpio::NoPP);
  delay_us (13);
  bit = pin.PinState (pin_);
  delay_us (45);
  return bit;
}

uint8_t ds18b20::read_byte ()
{
  uint8_t data =0;
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

char ds18b20::convertTemp ()
{
  uint16_t data = GetTemp ();
  char d = data >> 4;
  return d;
}