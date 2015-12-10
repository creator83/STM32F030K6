

#include "mcp3551.h"

// default constructor
mcp3551::mcp3551()
:spi1(spi::B, spi::div16, spi::neg, spi::first,spi::master, spi::bit8)
{
	delay_ms(1);	
	//pin.setDirPin(CS);
	spi1.Set_CS();
} //mcp3551

bool mcp3551::isReady()
{
  spi1.Clear_CS();
  delay_ms(80);
	if (!(GPIOB->IDR & (1 << 4)))
  //if (!(GPIOB->IDR & (1 << spi1.pins_d[spi1.port_][spi::MISO])))
  {
    return true;
  }
  else
  {
    spi1.Set_CS();
    return false;
  }
}

bool mcp3551::getCode()
{
	if (isReady())
	{
		spi_code.Byte[3] = 0x00;
		spi_code.Byte[2] = spi1.receive_8();
		spi_code.Byte[1] = spi1.receive_8();
		spi_code.Byte[0] = spi1.receive_8();
                
                spi1.Set_CS();
		
		OVH = spi_code.Byte[3] & (1 << 7);
		OVL = spi_code.Byte[3] & (1 << 8);
		if (OVH && OVL) return false;
		if (OVH && !OVL) spi_code.Byte [2] &= ~(1<<6|1<<7);
                delay_us (1);
		spi1.Clear_CS();
		if ((!OVH && (spi_code.Byte[2] & (1 << 5))) || OVL )
		{
			spi_code.Byte [2] |= (1 << 7|1 << 8);
			spi_code.Byte [3] = 0xFF;
		}
		spi1.Set_CS();
		byteCode = spi_code.ByteCode;
		return true;		
	}
	else return false;
}

bool mcp3551::getOVH()
{
	return OVH;
}

bool mcp3551::getOVL()
{
	return OVL;
}

float mcp3551::getTemp ()
{
  if (getCode())
  {
    float RTD = (r_val*(static_cast<float>(byteCode))/( 2097152.0 - static_cast<float>(byteCode)));
    RTD = (RTD/pt) - 1;
    return (RTD * (255.8723 + RTD * (9.6 + RTD * 0.878)));
  }
  else
    return 0;
}
