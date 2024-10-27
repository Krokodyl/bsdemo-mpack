#include "sounds.h"

u16 sfx_pitch[SFX_COUNT] = { 1, 1, 2, 2, 2, 2};

void playSound(u16 index) {
	/*
		pitch	pitch (0-15, 8=32khz)
		sfxIndex	effect index (0-15)
		volpan	volume(0..15) AND panning(0..15) (volume*16+pan)
	*/
	spcEffect(sfx_pitch[index],index,8*16+8);
	spcProcess();
}

void playMusic() {
	spcStop();
	if (music>0) {
		spcLoad(music);
	}
	
	u8 j;
	for (j=0;j<SFX_COUNT;j++) {
		spcLoadEffect(j);
	}
	if (music>0) {
		spcPlay(0);
	}
}

void initSpc() {
	spcBoot();
	
	// Set soundbanks in reverse order
	spcSetBank(&SOUNDBANK__);
	
    spcLoad(MOD_SFX);
	
	u8 j;
	spcStop(); spcLoad(0); 
	for (j=0;j<SFX_COUNT;j++) { 
        spcLoadEffect(j); 
    }
	music = MOD_MUSIC;

	spcSetModuleVolume(255);
}