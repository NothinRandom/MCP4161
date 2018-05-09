#include "MCP4161.h"

MCP4161::MCP4161(uint8_t csPin)
{
	_cs = csPin;
	pinMode(_cs, OUTPUT);
	digitalWrite(_cs, HIGH);
}

void MCP4161::begin()
{
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //enable spi, master, mode0, p12, 
}

int MCP4161::init() 
{
	byte value;
	digitalWrite(_cs, LOW);
	//send in the address and value via SPI:
	value = transfer(0x41);
	transfer(0x0F); //byte ret2 = transfer(0x0F);
	digitalWrite(_cs, HIGH);
	return value;
}

//true to increment, false to decrement
//p45, 8b
byte MCP4161::setValue(boolean direction)
{
	byte value;
	digitalWrite(_cs, LOW);
	if(direction)
		value = transfer(0x04);
	else
		value = transfer(0x08); 
	digitalWrite(_cs, HIGH);
	return value;
}

int MCP4161::readTCON() 
{
	byte value;
	digitalWrite(_cs, LOW);
	//send in the address and value via SPI:
	value = transfer(0x4C);
	transfer(0x00); //byte ret2 = transfer(0x00);
	digitalWrite(_cs, HIGH);
	return value;
}

int MCP4161::readStatus() 
{
	byte value;
	digitalWrite(_cs, LOW);
	//send in the address and value via SPI:
	value = transfer(0x5C);
	transfer(0x00); //byte ret2 = transfer(0x00);
	digitalWrite(_cs, HIGH);
	return value;
}

int MCP4161::setTap(int value) 
{
	byte hi;
	byte lo;
	digitalWrite(_cs, LOW);
	//  send in the address and value via SPI:
	hi = 0x03 & (value >> 8); //byte h = 0x03 & (value >> 8);
	lo = 0x00FF & value;; //byte l = 0x00FF & value;
	hi = transfer(hi); //hi = transfer(h);
	lo = transfer(lo); //lo = transfer(l);
	digitalWrite(_cs, HIGH);
	return (hi << 8) | lo;
}

byte MCP4161::transfer(volatile byte data)
{
	SPDR = data;
	while (!(SPSR & (1<<SPIF)));
	return SPDR;
}