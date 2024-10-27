#ifndef TRAIN_INCLUDE
#define TRAIN_INCLUDE

#include <snes.h>

#define VRAM_TILES_OFFSET_SPRITES 0x4000

#define RIGHT 0
#define LEFT 1

#define ID_GIRL			0
#define ID_BOY			1
#define ID_KROKO		2
#define ID_SATEBO_1		3
#define ID_SATEBO_2		4

// Rods
#define ID_E_RODS_1			10
#define ID_E_RODS_2			11
#define ID_C1_RODS_1		12
#define ID_C1_RODS_2		13
#define ID_C2_RODS_1		14
#define ID_C2_RODS_2		15
#define ID_C3_RODS_1		16
#define ID_C3_RODS_2		17
#define ID_C4_RODS_1		18
#define ID_C4_RODS_2		19

// Parabo + Engine
#define ID_ENGINE_1		21
#define ID_ENGINE_2		22
#define ID_ENGINE_3		23
// Chimneys
#define ID_CHIMNEY		20

#define ID_CAR1_1		24
#define ID_CAR1_2		25
#define ID_CAR2_1		26
#define ID_CAR2_2		27
#define ID_CAR3_1		28
#define ID_CAR3_2		29
#define ID_CAR4_1		30
#define ID_CAR4_2		31


#define PALETTE_GREENCAR	0
#define PALETTE_SATEBO		0
#define PALETTE_KROKO		1
#define PALETTE_ENGINE		2
#define PALETTE_BOY			3
#define PALETTE_BLUECAR		3
#define PALETTE_YELLOWCAR	5
#define PALETTE_GIRL		6
#define PALETTE_PINKCAR		7




extern char sprites_tiles, sprites_tiles_end;
extern char sprites_p, sprites_p_end;

typedef struct
{
	u16 x, y;
	u8 frame;
	u8 state;
	u8 direction;
} Train;

Train train;

void loadSprites();
void initTrain();
void drawRods();
void drawCharacters();
void animateRods(u8 id, u8 id2, u16 x, u16 y);

#endif // TRAIN_INCLUDE