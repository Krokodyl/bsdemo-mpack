#ifndef SOUNDS_INCLUDE
#define SOUNDS_INCLUDE

#include <snes.h>
#include "snd/soundbank.h"

#define SFX_COUNT 6

#define SFX_MENU_CHANGE 0
#define SFX_MENU_SELECT 1
#define SFX_NEXT_SLIDE 2
#define SFX_WRONG 3
#define SFX_COIN 4
#define SFX_PAGE 5

#define SFX_LETTER_DELETED 3
#define SFX_WORD_INVALID 4
#define SFX_WORD_CORRECT 5
#define SFX_WORD_WRONG 6
#define SFX_ACHOO 7

extern char SOUNDBANK__;

u8 music = 0;

void initSpc();
void playMusic();
void playSound(u16 index);

#endif // SOUNDS_INCLUDE