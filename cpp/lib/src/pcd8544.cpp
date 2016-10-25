#include "pcd8544.h"

uint8_t Pcd8544::screenBuffer [page][width] = {0};
Pcd8544::dmaMode Pcd8544::dmaMode_ = Pcd8544::off;

const char Pcd8544::null_val = 0;


char Pcd8544::Big_number[10][42] = {

0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0xef, 0xc7, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x00,   // 1
0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0xe0, 0xd0, 0xb8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x3b, 0x17, 0x0f, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00,   // 2
0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0x00, 0x10, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 3
0x00, 0xfc, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf8, 0xfc, 0x00, 0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x00,   // 4
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xb8, 0xd0, 0xe0, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 5
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x06, 0x02, 0x00, 0x00, 0x00, 0xef, 0xd7, 0xbb, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xb8, 0xd0, 0xe0, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 6
0x00, 0x00, 0x02, 0x06, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xc7, 0xef, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x7f, 0x00,   // 7
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0xef, 0xd7, 0xbb, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 8
0x00, 0xfc, 0xfa, 0xf6, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0xf6, 0xfa, 0xfc, 0x00, 0x00, 0x0f, 0x17, 0x3b, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xbb, 0xd7, 0xef, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f, 0x00,   // 9
// /
};

	
char Pcd8544::Med_number1[10][18]= {
	
0x00,0xF8,0xFC,0xFE,0x06,0x06,0xFE,0xFC,0xF8,
0x00,0x3F,0x7F,0xFF,0xC0,0xC0,0xFF,0x7F,0x3F, //0

0x00,0x0C,0x0C,0x0E,0xFE,0xFF,0xFF,0x00,0x00,
0x00,0x00,0x00,0x00,0x7F,0x7F,0x7F,0x00,0x00, //1

0x00,0x38,0x3C,0x3E,0x06,0x86,0xFE,0xFC,0x78,
0x00,0xC0,0xF0,0xFC,0xFF,0xCF,0xC7,0xC1,0xC0, //2

0x00,0x3C,0x3E,0xBE,0x86,0x86,0xFE,0xFC,0x78,
0x00,0x3C,0x7C,0xFD,0xC1,0xC1,0xFF,0x7F,0x3F, //3

0x00,0xC0,0xF0,0xFE,0x1E,0xFE,0xFE,0xFE,0x00,
0x00,0x1F,0x1F,0x1C,0x1C,0xFF,0xFF,0xFF,0x1C, //4

0x00,0xFE,0xFE,0xFE,0x46,0x66,0xE6,0xE6,0xC6,
0x00,0x3C,0x7C,0xFC,0xC0,0xC0,0xFF,0x7F,0x3F, //5

0x00,0xF8,0xFC,0xFE,0xC6,0xC6,0xDE,0xDC,0x98,
0x00,0x3F,0x7F,0xFF,0xC0,0xC0,0xFF,0x7F,0x3F, //6

0x00,0x06,0x06,0x06,0x86,0xFE,0xFE,0x3E,0x00,
0x00,0x00,0xC0,0xFC,0xFF,0x3F,0x03,0x00,0x00, //7

0x00,0x78,0xFC,0xFE,0x86,0x86,0xFE,0xFE,0x78,
0x00,0x3F,0x7F,0xFF,0xC1,0xC1,0xFF,0x7F,0x3F, //8

0x00,0xF8,0xFC,0xFE,0x06,0x06,0xFE,0xFC,0xF8,
0x00,0x33,0x77,0xF7,0xC6,0xC6,0xFF,0x7F,0x3F //9
};

Pcd8544::Pcd8544 (Spi &module)
{
	spimodule = &module;
	
	//Settings pins
	//CS
	spimodule->set_CS(Pcd8544Def::CsPort, Pcd8544Def::CsPin, Gpio::AF0);

	//SCK
	spimodule->set_SCK(Pcd8544Def::SckPort, Pcd8544Def::SckPin, Gpio::AF0);

	//MOSI
	spimodule->set_MOSI(Pcd8544Def::MosiPort, Pcd8544Def::MosiPin, Gpio::AF0);
	
	//DC
	dc.settingPinPort (Pcd8544Def::DcPort);
	dc.settingPin (Pcd8544Def::DcPin);
	//DC
	reset.settingPinPort (Pcd8544Def::RstPort);	
	reset.settingPin (Pcd8544Def::RstPin);
	
	//===Settings Spi===//
		//settings SPI
	spimodule->set_cpha(Spi::first);
	spimodule->set_cpol(Spi::neg);
	spimodule->set_baudrate(Spi::div16);
	spimodule->set_f_size(Spi::bit_8);
	spimodule->start();
	init ();
	dmaSetting ();
}

void Pcd8544::init ()
{
	reset.setPin (Pcd8544Def::RstPin);
	reset.clearPin (Pcd8544Def::RstPin);
	reset.setPin (Pcd8544Def::RstPin);
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

void Pcd8544::dmaSetting ()
{
	//settings spi dma
	SPI1->CR2 |= SPI_CR2_TXDMAEN;
	mem2spi1.setChannel (Dma::ch3);
	mem2spi1.setPtrPeriph ((uint32_t) (&(SPI1->DR)));
	mem2spi1.setSize (Dma::bit8, Dma::bit8);
	mem2spi1.setDirection (Dma::mem2periph);
	mem2spi1.setIncMem (true);
	mem2spi1.setIncPer (false);
	
	//settings mem2mem dma
	mem2buff.setChannel (Dma::ch2);
	mem2buff.setSize (Dma::bit8, Dma::bit8);
	mem2buff.setDirection (Dma::mem2periph);
	mem2buff.setMemToMem (true);
	mem2buff.setIncMem (true);
	mem2buff.setIncPer (true);
}

void Pcd8544::command (uint8_t comm)
{
	
	dc.clearPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	spimodule->put_data (comm);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::byte (uint8_t dta)
{
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	spimodule->put_data (dta);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::array (const uint8_t *dta, uint16_t n)
{
	for (uint16_t i=0;i<n;++i) 
	{
		while (!spimodule->flag_txe());
		spimodule->put_data (*dta++);
	}
}


void Pcd8544::data (uint8_t dta, uint16_t n)
{
	for (uint16_t i=0;i<n;++i) 
	{
		while (!spimodule->flag_txe());
		spimodule->put_data (dta);
	}	
}



void Pcd8544::clearScreen ()
{
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	data (0, page*width);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
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
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	data (0xFF, page*width);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::chipAssert ()
{
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
}

void Pcd8544::chipDisassert ()
{
	
}

void Pcd8544::character (uint8_t line , uint8_t position , const char ch, sFont & s)
{
	setLinePosition (line, position);
	const uint8_t *tempPtr = s.font;
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	array ((tempPtr+((ch-s.shift)*s.width)), s.width);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::character (const char ch, sFont & s)
{
	const uint8_t *tempPtr = s.font;
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	array ((tempPtr+((ch-s.shift)*s.width)), s.width);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::string (uint8_t line , uint8_t pos , const char *str, sFont &f, uint8_t interval)
{
	setLinePosition (line, pos);
	const uint8_t *tempPtr = f.font;
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	while (*str)
	{	
		array ((tempPtr+((*str++-f.shift)*f.width)), f.width);
		for (int8_t i=0;i<interval;++i) byte (0);
	}
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::parsingBin (uint8_t line , uint8_t pos, uint8_t interval, uint8_t number, sFont &f)
{
	uint8_t position = pos;
	for (uint8_t i=0;i<8;++i, position+=interval)
	{
		if (number&(1<<(7-i))) character (line, position, '1',f);
		else 	 character (line, position, '0',f);
	}
}

void Pcd8544::characterToBuffer (uint8_t line , uint8_t position , const char ch, sFont &s)
{
	const uint8_t *tempPtr = s.font+(ch-s.shift)*s.width;
	for (uint8_t i=0;i<s.width;++i,position++)
	{
		screenBuffer [line][position] = *tempPtr++;
	}
	
}

void Pcd8544::characterToBufferDma (uint8_t line , uint8_t position , const char ch, sFont &s)
{
	const uint8_t *tempPtr = s.font+(ch-s.shift)*s.width;
	mem2buff.setSources ((uint32_t) tempPtr, (uint32_t) &screenBuffer[line][position]);
	mem2buff.setLength (s.width);
	mem2buff.start ();
	while (!mem2buff.flagTcif());
	mem2buff.clearTcif();
	mem2buff.stop ();
}
void Pcd8544::stringToBuffer (uint8_t line , uint8_t position, const char *str, sFont &s, uint8_t interval)
{
	while (*str)
	{
		characterToBuffer (line, position, *str++, s);
		position += s.width+interval;
	}
}

void Pcd8544::stringToBufferDma (uint8_t line , uint8_t position, const char *str, sFont &s, uint8_t interval)
{
	while (*str)
	{
		characterToBufferDma (line, position, *str++, s);
		position += s.width+interval;
	}
}

void Pcd8544::drawBuffer ()
{
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	array (&screenBuffer[0][0], page*width);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::drawBuffer (uint8_t line, uint8_t x1, uint8_t x2)
{
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	array (&screenBuffer[line][0], x2-x1);
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::drawBufferDma ()
{
	setLinePosition (0, 0);
	mem2spi1.setPtrMem ((uint32_t)screenBuffer);
	mem2spi1.setLength (bufferSize);
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	mem2spi1.start ();
	while (!mem2spi1.flagTcif());
	mem2spi1.clearTcif();
	mem2spi1.stop ();
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
}

void Pcd8544::drawBufferDma (uint8_t line, uint8_t x1, uint8_t x2)
{
	setLinePosition (line, x1);
	mem2spi1.setPtrMem ((uint32_t)&screenBuffer[line][x1]);
	mem2spi1.setLength (x2-x1);
	dc.setPin (Pcd8544Def::DcPin);
	spimodule->assert_Cs(Pcd8544Def::CsPin);
	mem2spi1.start ();
	while (!mem2spi1.flagTcif());
	mem2spi1.clearTcif();
	mem2spi1.stop ();
	while (spimodule->flag_bsy());
	spimodule->disassert_Cs (Pcd8544Def::CsPin);
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
