#include "menu.h"

u16 ramAddress;
u16 shift;
u16 shift1;
u16 shift2;
u16 i;
u8 value;
u16 value16;
u8 mask;
u8 maskPalette  = 0x24; // palette 1 high priority
u8 maskPaletteSelected = 0x28; // palette 2 high priority


// updates the tilemap for the "time" option in wram
void drawMenuOption1() {
	// option 1
	ramAddress = VRAM_MAP_OFFSET_MENU+0x40;
	if (showTime==0) { // "Show time"
		shift = 0x80;
		if (selectedOption==OPT_SHOW_HIDE_TIME) shift += 0x200;
		for (i=0;i<0x80;i=i+2) {
			value16 = *((u16*)((&bg3_m) + (shift + i)));
			*((u16*)(&wram7f)+(0x1000+ramAddress+i)/2) = value16;
		}
	} else { // "Hide time"
		shift = 0x100;
		if (selectedOption==OPT_SHOW_HIDE_TIME) shift += 0x200;
		for (i=0;i<0x80;i=i+2) {
			value16 = *((u16*)((&bg3_m) + (shift + i)));
			*((u16*)(&wram7f)+(0x1000+ramAddress+i)/2) = value16;
		}
	}
}

// updates the tilemap for the "exit" option in wram
void drawMenuOption2() {
	// option 2
	ramAddress = VRAM_MAP_OFFSET_MENU+0x40+0x80;
	shift = 0x180;
	if (selectedOption==OPT_EXIT) shift += 0x200;
	for (i=0;i<0x80;i=i+2) {
		value16 = *((u16*)((&bg3_m) + (shift + i)));
		*((u16*)(&wram7f)+(0x1000+ramAddress+i)/2) = value16;
	}
}

// updates the tilemap for the "reboot" option in wram
void drawMenuOption3() {
	// option 3
	ramAddress = VRAM_MAP_OFFSET_MENU+0x40+0x100;
	shift = 0x200;
	if (selectedOption==OPT_REBOOT) shift += 0x200;
	for (i=0;i<0x80;i=i+2) {
		value16 = *((u16*)((&bg3_m) + (shift + i)));
		*((u16*)(&wram7f)+(0x1000+ramAddress+i)/2) = value16;
	}
}

// updates the tilemap for the whole menu in wram
void drawMenu() {
	// clear ram
	
	for (i=0;i<0x800;i++) {
		*((u8*)&wram7f+0x1000+i) = 0x00;
	}
	
	ramAddress = VRAM_MAP_OFFSET_MENU;
	// border top
	for (i=0;i<0x40;i++) {
		value = *((u8*)(&bg3_m + i));
		*((u8*)&wram7f+0x1000+ramAddress+i) = value;
	}
	
	drawMenuOption1();
	drawMenuOption2();
	drawMenuOption3();
	
	ramAddress = VRAM_MAP_OFFSET_MENU+0x40+0x180;
	// border bottom
	for (i=0;i<0x40;i++) {
		value = *((u8*)(&bg3_m + 0x40 + i));
		*((u8*)&wram7f+0x1000+ramAddress+i) = value;
	}
}

// copy the whole bg3 tilemap from wram to vram
void initMenu() {
	dmaCopyVram(&wram7f+0x1000, VRAM_MAP_OFFSET_BG3, 0x800);
}

// copy the menu tilemap from wram to vram
void dmaMenu() {
	dmaCopyVram(&wram7f+0x1000+VRAM_MAP_OFFSET_MENU, VRAM_MAP_OFFSET_BG3+(VRAM_MAP_OFFSET_MENU/2), 0x200);
}

// reads the joypad1 values and updates the menu accordingly
void readInputs() {
	pad0 = padsCurrent(0);
	if (pad0 & KEY_UP) {
		if (!padUp) {
			padUp=1;
			if (selectedOption>OPT_SHOW_HIDE_TIME) {
				selectedOption--;
			} else selectedOption=OPT_REBOOT;
			if (selectedOption==OPT_SHOW_HIDE_TIME) {
				drawMenuOption1();
				drawMenuOption2();
			}
			if (selectedOption==OPT_EXIT) {
				drawMenuOption2();
				drawMenuOption3();
			}
			if (selectedOption==OPT_REBOOT) {
				drawMenuOption3();
				drawMenuOption1();
			}
			playSound(SFX_MENU_CHANGE);
		}
	} else padUp = 0;
	if (pad0 & KEY_DOWN) {
		if (!padDown) {
			padDown=1;
			if (selectedOption<OPT_REBOOT) {
				selectedOption++;
			} else selectedOption=OPT_SHOW_HIDE_TIME;
			if (selectedOption==OPT_EXIT) {
				drawMenuOption1();
				drawMenuOption2();
			}
			if (selectedOption==OPT_REBOOT) {
				drawMenuOption2();
				drawMenuOption3();
			}
			if (selectedOption==OPT_SHOW_HIDE_TIME) {
				drawMenuOption3();
				drawMenuOption1();
			}
			playSound(SFX_MENU_CHANGE);
		}
	} else padDown = 0;
	if (pad0 & KEY_A) {
		if (!padA) {
			padA=1;
			if (selectedOption==OPT_SHOW_HIDE_TIME) {
				if (showTime==0) showTime=1;
				else showTime=0;
				drawMenuOption1();
			}
			if (selectedOption==OPT_REBOOT) {
				playSound(SFX_MENU_SELECT);
				spcFadeModuleVolume(0, 30);
				setFadeEffect(FADE_OUT);
				spcReset();
				bsRebootBios();
			}
			if (selectedOption==OPT_EXIT) {
				playSound(SFX_MENU_SELECT);
				spcFadeModuleVolume(0, 30);
				setFadeEffect(FADE_OUT);
				spcReset();
				bsReturnToTown();
			}
			playSound(SFX_MENU_SELECT);
		}
	} else padA = 0;
}


// prints the value on the BG3 at location
void printValue(u8 value, u16 mapRow, u16 mapCol, u16 valLength) {
	u8 col = (u8)(mapCol+valLength-1);
	u8 readChar = 0xE0+(value%10);
	*((u8*)&wram7f+0x1000+(0x40*mapRow)+(col*2)) = (readChar);
	*((u8*)&wram7f+0x1000+(0x40*(mapRow+1))+(col*2)) = (readChar+0x10);
	value = value/10;
	while (value>0) {
		col--;
		readChar = 0xE0+(value%10);
		*((u8*)&wram7f+0x1000+(0x40*mapRow)+(col*2)) = (readChar);
		*((u8*)&wram7f+0x1000+(0x40*(mapRow+1))+(col*2)) = (readChar+0x10);
		value = value/10;
	}
}