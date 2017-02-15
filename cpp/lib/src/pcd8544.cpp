#include "pcd8544.h"

uint8_t Pcd8544::screenBuffer [page][width] = {0};
Pcd8544::dmaMode Pcd8544::dmaMode_ = Pcd8544::off;

const char Pcd8544::null_val = 0;

Pcd8544::Pcd8544 (Spi & module, Gpio::Port csPort, uint8_t csPin, Gpio::Port dcPort, uint8_t dcPin, Gpio::Port rstPort, uint8_t rstPin)
:dc(dcPort, dcPin), rst (rstPort, rstPin), cs (csPort, csPin)
{
	spimodule = &module;
	
	//===Settings Spi===//
		//settings SPI
	spimodule->setCpha(Spi::cpha::first);
	spimodule->setCpol(Spi::cpol::neg);
	spimodule->setBaudrate(Spi::division::div16);
	spimodule->setFsize(Spi::fsize::bit_8);
	spimodule->start();
	init ();
}

void Pcd8544::init ()
{
	rst.set();
	rst.clear ();
	rst.set();
	command(lcd_setfunctionext);    
 command(lcd_setvop + 70); 
 command(lcd_tempcoef + temp3);
 command(lcd_setbias + bias_1_65);
 command(lcd_setfunction);
	command(lcd_displaynormal);
	clearScreen ();
}

void Pcd8544::dma (dmaMode m)
{
	
}

void Pcd8544::setDma (Dma::dmaChannel ch1, Dma::dmaChannel ch2)
{
 setSpiDma (ch1);
 setMemDma (ch2);
}

void Pcd8544::setSpiDma (Dma::dmaChannel spi)
{
 //settings spi dma
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
	mem2spi1.setChannel (spi);
	mem2spi1.setPtrPeriph ((uint32_t) (&(SPI1->DR)));
	mem2spi1.setSize (Dma::size::bit8, Dma::size::bit8);
	mem2spi1.setDirection (Dma::direction::mem2periph);
	mem2spi1.setIncMem (true);
	mem2spi1.setIncPer (false);
}

void Pcd8544::setMemDma (Dma::dmaChannel mem)
{
	//settings mem2mem dma
	mem2buff.setChannel (mem);
	mem2buff.setSize (Dma::size::bit8, Dma::size::bit8);
	mem2buff.setDirection (Dma::direction::mem2periph);
	mem2buff.setMemToMem (true);
	mem2buff.setIncMem (true);
	mem2buff.setIncPer (true); 
}

void Pcd8544::command (uint8_t comm)
{
	dc.clear ();;
	cs.clear ();
	spimodule->putData (comm);
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::byte (uint8_t dta)
{
	dc.set ();
	cs.clear ();
	spimodule->putData (dta);
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::array (const uint8_t *dta, uint16_t n)
{
	for (uint16_t i=0;i<n;++i) 
	{
		while (!spimodule->flagTxe());
		spimodule->putData (*dta++);
	}
}


void Pcd8544::data (uint8_t dta, uint16_t n)
{
	for (uint16_t i=0;i<n;++i) 
	{
		while (!spimodule->flagTxe());
		spimodule->putData (dta);
	}	
}

void Pcd8544::clearScreen ()
{
	dc.set();
	cs.clear ();
	data (0, page*width);
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::setPosition(uint8_t x, uint8_t y)
{
  command (lcd_setXaddr | x);
  command (lcd_setYaddr | y);
}

void Pcd8544::setLinePosition (uint8_t line, uint8_t position)
{
	command (lcd_setXaddr | position);
 command (lcd_setYaddr | line);
}

void  Pcd8544::clearScreen (uint8_t x,uint8_t y,uint8_t dx,uint8_t dy)
{
	
}

void Pcd8544::fillScreen ()
{
	dc.set ();
	cs.clear ();
	data (0xFF, page*width);
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::chipAssert ()
{
	dc.set ();
	cs.clear ();
}

void Pcd8544::chipDisassert ()
{
	cs.set ();
}

void Pcd8544::character (uint8_t line , uint8_t position ,  uint8_t ch, Font & s)
{
	setLinePosition (line, position);
	const uint8_t *tempPtr = s.getFont ();
	dc.set ();
	cs.clear ();
 for (uint8_t i=0;i<s.getHeight();++i)
 {
  setLinePosition (line+i, position);
  array ((tempPtr+((ch-s.getShift())*s.getWidth())), s.getWidth());
  while (spimodule->flagBsy());
  cs.set ();
 }
}

void Pcd8544::string (uint8_t line , uint8_t pos , const char *str, Font &f, uint8_t interval)
{
	uint8_t tempPos = pos;
	const uint8_t *tempPtr = f.getFont ();
	dc.set ();
	cs.clear ();
	while (*str)
	{	
  character (line, tempPos, *str++, f);
		tempPos += interval;
	}
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::characterToBuffer (uint8_t line , uint8_t position , uint8_t ch, Font &s)
{
const	uint8_t *tempPtr = s.getFont ()+(ch-s.getShift())*s.getWidth();
	for (uint8_t i=0;i<s.getWidth();++i)
	{
   for (uint8_t i=0;i<s.getHeight();++i)
  {
   screenBuffer [line+i][position] = *tempPtr++;
  }
	}
}

void Pcd8544::characterToBufferDma (uint8_t line , uint8_t position , uint8_t ch, Font &s)
{
	const uint8_t *tempPtr = s.getFont()+(ch-s.getShift())*s.getWidth();
	mem2buff.setSources ((uint32_t) tempPtr, (uint32_t) &screenBuffer[line][position]);
	mem2buff.setLength (s.getWidth());
	mem2buff.start ();
	while (!mem2buff.flagTcif());
	mem2buff.clearTcif();
	mem2buff.stop ();
}

void Pcd8544::stringToBuffer (uint8_t line , uint8_t position, const char *str, Font &s, uint8_t interval)
{
	while (*str)
	{
		characterToBuffer (line, position, *str++, s);
		position += s.getShift()+interval;
	}
}

void Pcd8544::stringToBufferDma (uint8_t line , uint8_t position, const char *str, Font &s, uint8_t interval)
{
	while (*str)
	{
		characterToBufferDma (line, position, *str++, s);
		position += s.getWidth()+interval;
	}
}

void Pcd8544::stringToBufferDma (uint8_t line , uint8_t position, const char *str, uint8_t size, Font &s, uint8_t interval)
{
	while (size--)
	{
		characterToBufferDma (line, position, *str++, s);
		position += s.getWidth() + interval;
	}
}

void Pcd8544::drawBuffer ()
{
	dc.set ();
	cs.clear ();
	array (&screenBuffer[0][0], page*width);
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::drawBuffer (uint8_t line, uint8_t x1, uint8_t x2)
{
	dc.set ();
	cs.clear ();
	array (&screenBuffer[line][0], x2-x1);
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::drawBufferDma ()
{
	setLinePosition (0, 0);
	mem2spi1.setPtrMem ((uint32_t)screenBuffer);
	mem2spi1.setLength (bufferSize);
	dc.set ();
 cs.clear ();
	mem2spi1.start ();
	while (!mem2spi1.flagTcif());
	mem2spi1.clearTcif();
	mem2spi1.stop ();
	while (spimodule->flagBsy());
	cs.set ();
}

void Pcd8544::drawBufferDma (uint8_t line, uint8_t x1, uint8_t x2)
{
	setLinePosition (line, x1);
	mem2spi1.setPtrMem ((uint32_t)&screenBuffer[line][x1]);
	mem2spi1.setLength (x2-x1);
	dc.set ();
	cs.clear ();
	mem2spi1.start ();
	while (!mem2spi1.flagTcif());
	mem2spi1.clearTcif();
	mem2spi1.stop ();
	while (spimodule->flagBsy());
	cs.set ();
}

/*

void pcd8544::bin_number (uint8_t x , uint8_t y , uint8_t num)
{
	gotoxy (x,y);
	for (uint8_t i=0;i<8;++i)
	{
		if (num&(1<<(7-i))) draw_char ('1');
		else 	 draw_char ('0');
	}
}

void pcd8544::draw_font(char * font, char ch)
{
	pin.setPin (DC);
	spi1.Clear_CS ();
	font = font +((ch-32)*6);
	//font++;
	for (uint8_t i=0;i<6;++i,++font)
	{
		while (!spi1.flag_txe());
		spi1.put_data (*font);
	}
	while (spi1.flag_bsy ());
	spi1.Set_CS ();
}

void pcd8544::draw_big_number(uint8_t x, uint8_t y, uint8_t ch)
{
	
	
	char *ptr = &Big_number [ch][0];
	for (uint8_t i=0;i<3;++i)
	{
		gotoxy (x,y+i);
		pin.setPin (DC);
		spi1.Clear_CS ();
		for (uint8_t j=0;j<14;++j, ptr++)
		{
			while (!spi1.flag_txe());
			spi1.put_data (*ptr);
		}
	}
	while (spi1.flag_bsy ());
	spi1.Set_CS ();
}

void pcd8544::draw_char(uint8_t x , uint8_t y , char ch)
{
	gotoxy (x,y);
	draw_font (NewFontLAT, ch);
}

void pcd8544::draw_char(char ch)
{
	draw_font (NewFontLAT, ch);
}

void draw_font_buffer(uint8_t * font, char ch)
{
}

void pcd8544::draw_char_buffer (uint8_t x , uint8_t y , char ch)
{
	char *ptr = &NewFontLAT [((ch-32)*6)];
	for (uint8_t i=0;i<6;++i,ptr++)
	{
		buffer [y][x+i]= *ptr;
	}
}

void pcd8544::string_buffer (uint8_t x , uint8_t y , char *str)
{
	uint16_t shift=0;
	while (*str)
	{
		draw_char_buffer (x+shift,y, *str);
		str++;
		shift+=6;
	}
	
}

void pcd8544::hor_line_buffer (uint8_t x1 , uint8_t x2,  uint8_t y1 , uint8_t t)
{
	uint8_t l = x2 - x1;
	uint8_t *ptr= &buffer [y1>>3][x1];
	uint8_t thick = 0;
	for (uint8_t i=0;i<t;++i)
	{
		thick |= 1 << i;
	}
	thick <<= y1%8;
	for (uint8_t i=0;i<l;++i,ptr++)
	{
		*ptr= thick;
	}
}

void pcd8544::ver_line_buffer (uint8_t x , uint8_t y1,  uint8_t dy, uint8_t thick)
{
	uint8_t *ptr;

	for (uint8_t i=0;i<dy;++i)
	{
		ptr = &buffer [y1+i][x];
		for (uint8_t j=0;j<thick;++j,ptr++)
		{
			*ptr = 0xFF;
		}
	}
}

void pcd8544::hor_line (uint8_t x1 , uint8_t x2,  uint8_t y , uint8_t t)
{
	uint8_t l = x2 - x1;
	uint8_t dy = y%8;
	uint8_t thick = 1 << dy;
	gotoxy (x1,(y>>3));
		
	for (uint8_t i=0;i<t;++i)
	{
		thick |= 1 << (i+dy);
	}
	pin.setPin (DC);
	spi1.Clear_CS ();
	for (uint8_t i=0;i<l;++i)
	{
		while (!spi1.flag_txe());
		spi1.put_data (thick);
	}
	while (spi1.flag_bsy ());
	spi1.Set_CS ();
}
void pcd8544::string_screen (uint8_t x , uint8_t y , char *str)
{
	gotoxy (x,y);
	while (*str)
	{
		draw_char (*str);
		str++;
	}
	
}








void pcd8544::refresh_buffer ()
{
	
}

void pcd8544::draw_picture (const char * pic, uint16_t l)
{
	gotoxy(0,0);
	mem2spi1.set_mem ((uint32_t)pic);
	mem2spi1.set_inc_mem (true);
	mem2spi1.set_length (l);
	assert_chip ();
	mem2spi1.start();	
}



void pcd8544::pixel (uint8_t x , uint8_t y)
{
	char i;
  i = y%8;
  gotoxy ( x, y>>3);
  send_byte(1<<i);
}

void pcd8544::assert_chip ()
{
	pin.setPin (DC);
	spi1.Clear_CS ();
}

uint32_t * pcd8544::buffer_adress ()
{
	return (uint32_t *) buffer;
}

void pcd8544::clear_buffer ()
{
	gotoxy(0,0);
	pin.setPin (DC);
	spi1.Clear_CS ();
  for (int i=0 ;i<page*width ;++i ) 
	{
		while (!spi1.flag_txe());
		spi1.put_data (0);	
	}
	while (spi1.flag_bsy ());
	spi1.Set_CS ();
}

void pcd8544::draw_buffer ()
{
	
	uint8_t * ptr = &buffer[0][0];
  gotoxy(0,0);
	pin.setPin (DC);
	spi1.Clear_CS ();
  for (int i=0 ;i<page*width ;++i,ptr++ ) 
	{
		while (!spi1.flag_txe());
		spi1.put_data (*ptr);	
	}
	while (spi1.flag_bsy ());
	spi1.Set_CS ();

	
}

void pcd8544::point_buffer (uint8_t x, uint8_t y, uint8_t t)
{
	uint8_t *ptr = &buffer [y][x];
	uint8_t thick = 0;
	for (uint8_t i=0;i<t;++i)
	{
		thick |= 1 <<(7-i);
	}
	for (uint8_t i=0;i<t;++i,ptr++)
	{
		*ptr= thick;
	}
}

void pcd8544::big_number_buffer (uint8_t x , uint8_t y , uint8_t num)
{
	char *ptr = &Big_number [num][0];
	for (uint8_t i=0, k=0;i<3;++i,k+=14)
	{
		for (uint8_t j=0;j<14;++j,ptr++)
		{
			buffer [y+i][x+j] = *ptr;
		}
	}

	
}

void pcd8544::med_number_buffer (uint8_t x , uint8_t y , uint8_t num)
{
	char *ptr = &Med_number [num][0];
	for (uint8_t i=0;i<2;++i)
	{
		for (uint8_t j=0;j<8;++j,ptr++)
		{
			buffer [y+i][x+j] = *ptr;
		}
	}
}

void pcd8544::string_number_buffer (uint8_t x , uint8_t y , uint8_t *arr, uint8_t l)
{
	for (uint8_t i=0,shift=0;i<l;++i, shift +=16)
	{
		big_number_buffer (x+shift,y, *(arr+i));
	}
}

void pcd8544::string_numberM_buffer (uint8_t x , uint8_t y , uint8_t *arr, uint8_t l)
{
	for (uint8_t i=0,shift=0;i<l;++i, shift +=8)
	{
		med_number_buffer (x+shift,y, *(arr+i));
	}
}
void pcd8544::clear_buffer (uint8_t x,uint8_t y,uint8_t dx,uint8_t dy)
{

	mem2buff.set_mem ((uint32_t)&null_val);
	mem2buff.set_inc_mem (false);
	mem2buff.set_inc_per (true);
	for (uint8_t i=0;i<dy;++i)
	{
		mem2buff.set_destination ((uint32_t)&buffer[y+i][x]);
		mem2buff.set_length (dx);
		mem2buff.start ();
	}	
}

void pcd8544::desassert_chip ()
{
	while (spi1.flag_ftvl());
	while (spi1.flag_bsy());
	spi1.Set_CS();
}

void pcd8544::ver_line (uint8_t x , uint8_t y1,  uint8_t y2, uint8_t thick)
{
	
}*/
