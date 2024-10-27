#ifndef SEA_INCLUDE
#define SEA_INCLUDE

#include <snes.h>

#define VRAM_TILES_OFFSET_SEA 0x04D0
#define SEA_ANIM_COUNT 6

extern char sea_waves_tiles, sea_waves_tiles_end;

u8 seaFrame = 0;
u8 seaState = 0;

void updateSeaWaves();
void dmaSeaWaves();
void initScrollingEffect();
void updateScrollingEffect();

#endif // SEA_INCLUDE