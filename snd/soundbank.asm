;************************************************
; snesmod soundbank data                        *
; total size:      16448 bytes                  *
;************************************************

.include "hdr.asm"

.BANK 5
.SECTION "SOUNDBANK" ; need dedicated bank(s)

SOUNDBANK__:
.incbin "snd/soundbank.bnk"
.ENDS
