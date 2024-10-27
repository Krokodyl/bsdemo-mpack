#include "bstime.h"

void initBSTime() {
	bstime.mth = 0;
	bstime.day = 0;
	bstime.hrs = 0;
	bstime.sec = 0;
	bstime.min = 0;
}

// writes the bs date in wram
void printDate() {
	u8 value = bstime.mth;
	u8 readChar = (value/10); // tens
	
	u16 ramAddress = VRAM_MAP_OFFSET_MENU+0x5A; // skips top border + half first line
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = (value%10); // units
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = 0x0B; // '/'
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	value = bstime.day;
	readChar = (value/10); // tens
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = (value%10); // units
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
}

// writes the bs time in wram
void printTime() {
	u8 value = bstime.hrs;
	u8 readChar = (value/10); // tens
	
	u16 ramAddress = VRAM_MAP_OFFSET_MENU+0x66; // skips top border + half first line + date
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = (value%10); // units
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = 0x0A; // ':'
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	value = bstime.min;
	readChar = (value/10); // tens
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = (value%10); // units
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = 0x0A; // ':'
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	value = bstime.sec;
	readChar = (value/10); // tens
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
	readChar = (value%10); // units
	*((u8*)&wram7f+0x1000+ramAddress) = readChar | 0xE0;
	*((u8*)&wram7f+0x1000+ramAddress+0x40) = readChar | 0xF0;
	ramAddress+=2;
	
}