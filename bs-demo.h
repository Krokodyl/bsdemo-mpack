#ifndef BSDEMO_INCLUDE
#define BSDEMO_INCLUDE

#include <snes.h>
#include "src/bstime.h"
#include "src/sounds.h"
#include "src/train.h"
#include "src/menu.h"
#include "src/sea.h"

extern char bg1_tiles, bg1_tiles_end;
extern char bg1_p, bg1_p_end;
extern char bg1_m, bg1_m_end;

extern char bg2_tiles, bg2_tiles_end;
extern char bg2_p, bg2_p_end;
extern char bg2_m, bg2_m_end;

extern char bg3_tiles, bg3_tiles_end;
extern char bg3_p, bg3_p_end;
extern char bg3_m, bg3_m_end;

extern char font_tiles, font_tiles_end;

#define BG1 0
#define BG2 1
#define BG3 2
#define BG4 3

#define VRAM_MAP_OFFSET_BG1 0x7400
#define VRAM_MAP_OFFSET_BG2 0x7800
#define VRAM_TILES_OFFSET_BG1 0x0000
#define VRAM_TILES_OFFSET_BG2 0x1000


// Joypad
u16 pad0;
u8 padA;
u8 padUp, padDown;

#define OPT_SHOW_HIDE_TIME 1
#define OPT_EXIT 2
#define OPT_REBOOT 3

u8 selectedOption = 2;

u8 showTime = 0; // 0="Show time" 1="Hide time"

#endif // BSDEMO_INCLUDE