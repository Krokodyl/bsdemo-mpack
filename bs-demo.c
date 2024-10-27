/*---------------------------------------------------------------------------------

Main file

---------------------------------------------------------------------------------*/
#include "bs-demo.h"

void vblank(){
	spcProcess();
	WaitForVBlank();
}

//---------------------------------------------------------------------------------
int main(void)
{
	
	initSpc();
	
    bgInitMapSet(BG1, &bg1_m, (&bg1_m_end - &bg1_m), SC_32x32, VRAM_MAP_OFFSET_BG1);
	bgInitTileSet(BG1, &bg1_tiles, &bg1_p, 1, (&bg1_tiles_end - &bg1_tiles), (&bg1_p_end - &bg1_p), BG_16COLORS, VRAM_TILES_OFFSET_BG1);
    bgInitMapSet(BG2, &bg2_m, (&bg2_m_end - &bg2_m), SC_32x32, VRAM_MAP_OFFSET_BG2);
	bgInitTileSet(BG2, &bg2_tiles, &bg2_p, 2, (&bg2_tiles_end - &bg2_tiles), (&bg2_p_end - &bg2_p), BG_16COLORS, VRAM_TILES_OFFSET_BG2);	
	
	bgInitTileSet(BG3, &bg3_tiles, &bg3_p, 0, (&bg3_tiles_end - &bg3_tiles), (&bg3_p_end - &bg3_p), BG_4COLORS, VRAM_TILES_OFFSET_BG3);	
	bgSetMapPtr(BG3, VRAM_MAP_OFFSET_BG3, SC_32x32);
	
	bgInitTileSetData(BG3, &font_tiles, (&font_tiles_end - &font_tiles), VRAM_TILES_OFFSET_FONT);
	
	// bg3 map
	drawMenu();
	initMenu();

	initBSTime();
	bsTimeReset();
	
	
	playMusic();

    setMode(BG_MODE1, BG3_MODE1_PRIORITY_HIGH);
	
	bgSetScroll(BG1, 0, -1);
	bgSetScroll(BG2, 0, -1);
	bgSetScroll(BG3, 0, -1);
	
	initTrain();
	loadSprites();
	drawTrain();

	setFadeEffect(FADE_IN);
    //setScreenOn();

	initScrollingEffect();

	// main loop
    while (1)
    {
		
		dmaMenu();

		updateSeaWaves();
		dmaSeaWaves();
		updateScrollingEffect();
		
		updateTrain();
		drawTrain();
		animateTrain();
		
		if (showTime) {
			bsTimeUpdate(&bstime);
			printDate();
			printTime();
		}
		
		
		readInputs();
		vblank();
    }
    return 0;
}
