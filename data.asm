.include "hdr.asm"

.SECTION "HeaderSafety" BANK 0 SLOT 3 ORGA $7FB0 FORCE
.DB $30 
.DB $31
.ends

;.SECTION "ReturnToTownData" BANK 0 SLOT 3 ORGA $7F80 FORCE
;.incbin "bs-features.data"
;.ENDS

.RAMSECTION ".section7f" BANK $7F SLOT 3
wram7f		DB
.ENDS

.section ".rodata1" superfree

bg1_tiles: .incbin "img/bg1.pic"
bg1_tiles_end

sea_waves_tiles: .incbin "img/sea-waves.pic"
sea_waves_tiles_end

bg2_tiles: .incbin "img/bg2.pic"
bg2_tiles_end

.ends

.section ".rodata2" superfree

bg1_m: .incbin "img/bg1.map"
bg1_m_end:

bg2_m: .incbin "img/bg2.map"
bg2_m_end:

bg1_p: .incbin "img/bg1.pal"
bg1_p_end:

bg2_p: .incbin "img/bg2.pal"
bg2_p_end:

.ends

.section ".bg3" superfree

bg3_tiles: .incbin "img/bg3.pic"
bg3_tiles_end

bg3_m: .incbin "img/bg3.map"
bg3_m_end:

bg3_p: .incbin "img/bg3.pal"
bg3_p_end:

.ends


.section ".font" superfree
font_tiles: 
.incbin "img/font.pic"
font_tiles_end
.ends


.section ".sprites" superfree

sprites_tiles: .incbin "img/sprites.pic"
sprites_tiles_end

sprites_p: .incbin "img/sprites.pal"
sprites_p_end:

.ends
