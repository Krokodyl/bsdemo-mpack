#ifndef BSTIME_INCLUDE
#define BSTIME_INCLUDE

#include <snes.h>
#include "../bs-demo.h"


#define VRAM_MAP_OFFSET_MENU 0x400

/*
sec     seconds		(00 - 3B)
min     minutes		(00 - 3B)
hrs     hours		(00 - 17)
wda     week day	(01 - 07) (01 = Sunday, 07 = Saturday)
day     day of the month (00 - 1F)
mth     month		(01 - 0C)
 */
typedef struct
{
	u8 sec, min, hrs, wda, day, mth;
} BSTime;
	
BSTime bstime;

void initBSTime();
void printTime();
void printDate();

#endif // BSTIME_INCLUDE