ifeq ($(strip $(PVSNESLIB_HOME)),)
$(error "Please create an environment variable PVSNESLIB_HOME by following this guide: https://github.com/alekmaul/pvsneslib/wiki/Installation")
endif

export SFCBSCONV := tools/sfc-bs-converter-1.0
# OR
# export SFCBSCONV := java -jar tools/sfc-bs-converter-1.0.jar

AUDIOFILES := snd/sfx.it snd/music.it 
export SOUNDBANK := snd/soundbank

include ${PVSNESLIB_HOME}/devkitsnes/snes_rules

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
# ROMNAME is used in snes_rules file
export ROMNAME := bs-demo-mpack

SMCONVFLAGS	:= -s -o $(SOUNDBANK) -V -b 5
musics: $(SOUNDBANK).obj

all: musics bitmaps $(ROMNAME).sfc sfcbsconv

clean: cleanBuildRes cleanRom cleanGfx cleanAudio cleanBS

cleanBS:
	@echo clean BS rom
	@rm -f $(ROMNAME).bs

# -d 28 -m 12	Broadcast date 12/28
# -b 29 80		Skip St.GIGA intro (0x80)
sfcbsconv:
	@echo Converting rom for the Satellaview
	$(SFCBSCONV) -d 28 -m 12 -b 29 80 -t "BS-DEMO-MPACK" -i $(ROMNAME).sfc -o $(ROMNAME).bs $<
	
#---------------------------------------------------------------------------------
bg2.pic: img/bg2.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -s 8 -o 128 -u 128 -e 2 -p -t bmp -m -i $<

bg1.pic: img/bg1.bmp
	@echo convert bitmap ... $(notdir $<)
	$(GFXCONV) -s 8 -o 16 -u 16 -e 1 -p -t bmp -m -i $<

sea-waves.pic: img/sea-waves.png
	@echo convert bitmap ... $(notdir $<)
	$(GFXCONV) -s 8 -u 16 -e 1 -t png -i $<

bg3.pic: img/bg3.png
	@echo convert bitmap ... $(notdir $<)
	$(GFXCONV) -s 8 -o 16 -u 4 -e 0 -p -t png -m -g -i $<
	
font.pic: img/font.png
	@echo convert bitmap ... $(notdir $<)
	$(GFXCONV) -s 8 -o 16 -u 4 -e 1 -t png -m -R -i $<
	
sprites.pic: img/sprites.png
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -p -o 128 -s 8 -R -i $<
	
bitmaps : bg1.pic bg2.pic bg3.pic \
font.pic sprites.pic \
sea-waves.pic
