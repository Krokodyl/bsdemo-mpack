.include "hdr.asm"

;
; Address in WRAM to save the bs town values
; (used for exit to town/reboot functions)
; requires $2000 bytes after
; requires 2 bytes before
.EQU TOWN_ADDR           $7FE000

.BASE 0 .BANK 0
.SECTION ".satellaview_text" FORCE

;---------- RETURN-TO-TOWN FEATURE ----------
;
bsStart:
  JML bsStart+4
  JML bsSaveTownRam

; 
; Saves the first $2000 bytes of WRAM to TOWN_ADDR
; Saves the stack pointer to TOWN_ADDR-2
;
bsSaveTownRam:
  SEI
  CLC
  XCE   ; SEI CLC XCE makes the .sfc boot

  REP #$30
  TSC
  STA TOWN_ADDR-2
  SEP #$20
  LDA #$7E
  PHA
  PLB
  REP #$30
  LDX #$1FFE
  bsSaveTownRamLoop:
  LDA $0000,X
  STA TOWN_ADDR,X
  DEX
  DEX
  BPL bsSaveTownRamLoop
  JML tcc__start

;
; Required for the bsReturnToTown function
;
bsVBlank:
  PHP
  REP #$30
  PHA
  LDA TOWN_ADDR
  CLC
  ADC TOWN_ADDR+2
  CMP #$FFFF
  BEQ skipNormalNMI
  PLA
  PLP
  JML VBlank
  skipNormalNMI:
  PLA
  PLP
  RTI

bsReturnToTown:
  JMP.l (bsReturnToTown+4)

  PHP
  JSL spcReset    ; reset apu driver
  PLP

  SEP #$20
  LDA #$00
  STA $4200       ; disable NMI

  REP #$30
  LDX #$1FFE
  copyLoop2:
  LDA TOWN_ADDR,X
  STA $0000,X       ; restore ram
  DEX
  DEX
  BPL copyLoop2
  REP #$30
  LDA TOWN_ADDR-2   ; restore stack pointer
  TCS

  ; this magic number tells the "pvsneslib" NMI to do nothing
  ; while we haven't handed the execution back to the bsx NMI
  ; see bsVBlank
  REP #$30
  LDA #$2812    ; magic number
  STA TOWN_ADDR
  LDA #$D7ED    ; complement to magic number
  STA TOWN_ADDR+2

  SEP #$20
  LDA #$80
  PHA
  PLB
  STA $085000
  STA $0E5000

  SEP #$30
  JSL $99D732
  JSL $81C210
  JSL $81C29A
  JSL $80937F
  LDX $13B2
  BEQ bsReturnToTownSkip
  PHK
  PEA bsReturnToTownBack-1
  PHB
  PEA.w $7E00
  PLB
  PLB
  JML $80EB99
bsReturnToTownBack: 
.ASSUME p=20
bsReturnToTownSkip: 
  REP #$30
  STZ $0CDE
  LDA.w #$0099
  STA.b $BE
  LDA.w #$D69A
  JSL $81C2B0
  SEP #$20
  
  LDA #$80
  STA $075000
  
  LDA #$81
  STA $4200       ; enable NMI
  LDA $4210       

  JML $80BC27
RTL

;---------- RESET-BIOS FEATURE ----------
;
; void bsRebootBios();
bsRebootBios:
  PHP
  JSL spcReset
  PLP
	SEP #$20
  JSL $105C3C.l

;---------- TIME-CHANNEL FEATURE ----------
;

bsTimeReset:
php
	REP #$20
  LDA #$0000.w
  STA $00218E.l
  LDA #$0001.w
  STA $002191.l
  NOP
  NOP
  NOP
  NOP
  STA $002192.l
  plp
  RTL
bsTimeUpdate:
  php
  SEP #$20
  LDA $002190.l
  AND #$FF
  BNE bsTimeDataFound
  plp
  RTL

  bsTimeDataFound:
	
  phb
  phx

	sep #$20
    lda 10,s                            ; bank
    pha
    plb

    rep #$20                            ; address
    lda 8,s
    tax

	sep #$20

  LDA $002192.l
  LDA $002192.l
  LDA $002192.l
  LDA $002192.l							
  LDA $002192.l
  LDA $002192.l
  LDA $002192.l
  LDA $002192.l
  LDA $002192.l
  LDA $002192.l     ; unused header (10 bytes)
  LDA $002192.l
  sta.w 0,x
  LDA $002192.l
  sta.w 1,x
  LDA $002192.l
  sta.w 2,x
  LDA $002192.l
  sta.w 3,x
  LDA $002192.l
  sta.w 4,x
  LDA $002192.l
  sta.w 5,x
  LDA $002192.l
  LDA $002192.l
  LDA $002192.l
  LDA $002192.l     ; unused stuff
  plx
  plb
  jsl bsTimeReset
  plp
  RTL




.ENDS

.BASE 0 .BANK 0
.SECTION ".sound_bs_text" FORCE

;---------------------------------------------------------------------------------
; Resets the snesmod APU driver to the initial state
; (necessary for the "reboot bios" and "return to town" features)
spcReset:

	SEP #$20
	LDA #$00
	PHA
	PLB         ;bank 00

  LDA #$07
	STA $2140   ;snesmod code 07 = reset
	STA $0044

  LDA $0045
  INC A
	STA $2141   ;validation data must different from previous value
	STA $0045

  REP #$10
  SEP #$20
  checkAABB:
  LDX $2140
  CPX #$BBAA
  BNE checkAABB ;wait for completed reset

	RTL


.ENDS
