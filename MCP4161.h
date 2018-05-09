#ifndef MCP4161_h
#define MCP4161_h

#if (ARDUINO >= 100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class MCP4161
{
	public:
		MCP4161(uint8_t csPin);
		void begin();
		int init();	
		byte setValue(boolean direction);
		int readTCON();
		int readStatus();
		int setTap(int value);
		
	private:
		uint8_t _cs;
		byte transfer(byte data);
};

#endif

