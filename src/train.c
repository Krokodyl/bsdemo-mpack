#include "train.h"

void initTrain() {
	train.x = 0x190;
	train.y = 93;
	train.frame = 0;
	train.state = 0;
	train.direction = RIGHT;
}

void loadSprites() {
	oamInitGfxSet(&sprites_tiles, (&sprites_tiles_end - &sprites_tiles), &sprites_p, (&sprites_p_end - &sprites_p), 0, VRAM_TILES_OFFSET_SPRITES, OBJ_SIZE8_L16);
}

void drawTrain() {
	oamSetEx(ID_ENGINE_1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_ENGINE_2*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_ENGINE_3*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CHIMNEY*4, OBJ_SMALL, OBJ_SHOW);
	oamSetEx(ID_CAR1_1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CAR1_2*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CAR2_1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CAR2_2*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CAR3_1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CAR3_2*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CAR4_1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_CAR4_2*4, OBJ_LARGE, OBJ_SHOW);
	oamSet(ID_ENGINE_1*4, train.x, train.y, 3, 0, 0, 0x00, PALETTE_ENGINE); // engine1
	oamSet(ID_ENGINE_2*4, train.x, train.y+16, 3, 0, 0, 0x20, PALETTE_ENGINE); // engine2
	oamSet(ID_ENGINE_3*4, train.x+16, train.y+16, 3, 0, 0, 0x22, PALETTE_ENGINE); // engine3
	oamSet(ID_CHIMNEY*4, train.x+16, train.y+16, 3, 0, 0, 0x02, PALETTE_ENGINE); // chimney
	oamSet(ID_CAR1_1*4, train.x-32, train.y+16, 3, 0, 0, 0x24, PALETTE_BLUECAR); // car1
	oamSet(ID_CAR1_2*4, train.x-16, train.y+16, 3, 0, 0, 0x26, PALETTE_BLUECAR); // car1
	oamSet(ID_CAR2_1*4, train.x-64, train.y+16, 3, 0, 0, 0x24, PALETTE_YELLOWCAR); // car2
	oamSet(ID_CAR2_2*4, train.x-48, train.y+16, 3, 0, 0, 0x26, PALETTE_YELLOWCAR); // car2
	oamSet(ID_CAR3_1*4, train.x-96, train.y+16, 3, 0, 0, 0x24, PALETTE_PINKCAR); // car3
	oamSet(ID_CAR3_2*4, train.x-80, train.y+16, 3, 0, 0, 0x26, PALETTE_PINKCAR); // car3
	oamSet(ID_CAR4_1*4, train.x-128, train.y+16, 3, 0, 0, 0x28, PALETTE_GREENCAR); // car4
	oamSet(ID_CAR4_2*4, train.x-112, train.y+16, 3, 0, 0, 0x2A, PALETTE_GREENCAR); // car4
	drawRods();
	drawCharacters();
}

void drawRods() {
	oamSetEx(ID_E_RODS_1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_E_RODS_2*4, OBJ_LARGE, OBJ_SHOW);
	oamSet(ID_E_RODS_1*4, train.x, train.y+25, 3, 0, 0, 0x40, PALETTE_ENGINE);
	oamSet(ID_E_RODS_2*4, train.x+16, train.y+25, 3, 0, 0, 0x42, PALETTE_ENGINE);
}

void drawCharacters() {
	// girl
	oamSetEx(ID_GIRL*4, OBJ_LARGE, OBJ_SHOW);
	oamSet(ID_GIRL*4, train.x-32, train.y+8, 3, 0, 0, 0x04, PALETTE_GIRL);
	// boy
	oamSetEx(ID_BOY*4, OBJ_LARGE, OBJ_SHOW);
	oamSet(ID_BOY*4, train.x-64, train.y+8, 3, 0, 0, 0x06, PALETTE_BOY);
	// kroko
	oamSetEx(ID_KROKO*4, OBJ_LARGE, OBJ_SHOW);
	oamSet(ID_KROKO*4, train.x-96, train.y+8, 3, 0, 0, 0x08, PALETTE_KROKO);
	// satebo
	oamSetEx(ID_SATEBO_1*4, OBJ_LARGE, OBJ_SHOW);
	oamSetEx(ID_SATEBO_2*4, OBJ_LARGE, OBJ_SHOW);
	oamSet(ID_SATEBO_1*4, train.x-128, train.y+8, 3, 0, 0, 0x0C, PALETTE_SATEBO);
	oamSet(ID_SATEBO_2*4, train.x-112, train.y+8, 3, 0, 0, 0x0E, PALETTE_SATEBO);
	
}

void animateTrain() {
	oamSetXY(ID_ENGINE_1*4, train.x, train.y); // engine1
	oamSetXY(ID_ENGINE_2*4, train.x, train.y+16); // engine2
	oamSetXY(ID_ENGINE_3*4, train.x+16, train.y+16); // engine3
	oamSetXY(ID_CHIMNEY*4, train.x+16, train.y+16); // chimney
	oamSetXY(ID_CAR1_1*4, train.x-32, train.y+16); // car1
	oamSetXY(ID_CAR1_2*4, train.x-16, train.y+16); // car1
	oamSetXY(ID_CAR2_1*4, train.x-64, train.y+16); // car2
	oamSetXY(ID_CAR2_2*4, train.x-48, train.y+16); // car2
	oamSetXY(ID_CAR3_1*4, train.x-96, train.y+16); // car3
	oamSetXY(ID_CAR3_2*4, train.x-80, train.y+16); // car3
	oamSetXY(ID_CAR4_1*4, train.x-128, train.y+16); // car4
	oamSetXY(ID_CAR4_2*4, train.x-112, train.y+16); // car4
	animateRods(ID_E_RODS_1, ID_E_RODS_2, train.x, train.y+25);
	if (train.state==0 || train.state==2) {
		oamSetGfxOffset(ID_SATEBO_1*4, 0x0C);
		oamSetGfxOffset(ID_SATEBO_2*4, 0x0E);
		oamSetXY(ID_SATEBO_1*4, train.x-128, train.y+8);
		oamSetXY(ID_SATEBO_2*4, train.x-112, train.y+8);
		oamSetGfxOffset(ID_CHIMNEY*4, 0x02);
		oamSetXY(ID_GIRL*4, train.x-32, train.y+7);
		oamSetXY(ID_BOY*4, train.x-64, train.y+8);
		oamSetXY(ID_KROKO*4, train.x-96, train.y+7);
		
	}
	if (train.state==1 || train.state==3) {
		oamSetGfxOffset(ID_SATEBO_1*4, 0x2C);
		oamSetGfxOffset(ID_SATEBO_2*4, 0x2E);
		oamSetXY(ID_SATEBO_1*4, train.x-128, train.y+7);
		oamSetXY(ID_SATEBO_2*4, train.x-112, train.y+7);
		oamSetGfxOffset(ID_CHIMNEY*4, 0x03);
		oamSetXY(ID_GIRL*4, train.x-32, train.y+8);
		oamSetXY(ID_BOY*4, train.x-64, train.y+7);
		oamSetXY(ID_KROKO*4, train.x-96, train.y+8);
	}
}

void animateRods(u8 id, u8 id2, u16 x, u16 y) {
	if (train.state==0) {
		oamSetXY(id*4, x, y+1);
		oamSetXY(id2*4, x+16, y+1);
	}
	if (train.state==1) {
		oamSetXY(id*4, x-1, y);
		oamSetXY(id2*4, x+16-1, y);
	}
	if (train.state==2) {
		oamSetXY(id*4, x, y-1);
		oamSetXY(id2*4, x+16, y-1);
	}
	if (train.state==3) {
		oamSetXY(id*4, x+1, y);
		oamSetXY(id2*4, x+16+1, y);
	}
}

void updateTrain() {
	train.frame++;
	train.x++;
	if (train.frame==8) {
		train.frame=0;
		train.state++;
	}
	if (train.state==4) {
		train.state=0;
	}
}