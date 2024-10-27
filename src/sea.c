#include "sea.h"


void updateSeaWaves() {
    seaFrame++;
    if (seaFrame==8) {
        seaFrame=0;
        seaState++;
        if (seaState==SEA_ANIM_COUNT) {
            seaState=0;
        }
    }
}

// copy the sea waves tiles to vram
void dmaSeaWaves() {
    dmaCopyVram(&sea_waves_tiles+(0x200*seaState), VRAM_TILES_OFFSET_SEA, 0x200);
}

void initScrollingEffect() {
    // Init HDMA table
    // 72 lines with 1 scrolling effect (top of screen)
    // Next 88 lines with 2 scrolling effect (middle of screen)
    // Next 64 lines with 4 scrolling effect (end of screen)
    HDMATable16[0] = 72;
    *(u16 *)&(HDMATable16 + 1) = 0;
    HDMATable16[3] = 88;
    *(u16 *)&(HDMATable16 + 4) = 0;
    HDMATable16[6] = 64;
    *(u16 *)&(HDMATable16 + 7) = 0;
    HDMATable16[9] = 0x00; // end of hdma table
}

void updateScrollingEffect() {
     setParallaxScrolling(0); // BG1
 
        // Change scrolling inside HDMA table
        *(u16 *)&(HDMATable16 + 1) += 1;
        *(u16 *)&(HDMATable16 + 4) += 0;
        *(u16 *)&(HDMATable16 + 7) -= 1;
}