; Checking on which system is program running
; August 25th, 2020
;
; Comment added: January 7-8th, 2021.
;
; The goal of this software is to check if it's running
; on Commodore 128 and avoid running on that machine.
; It's something similar to Windows' newer programs startup
; code which on MS-DOS prints "This program cannot be run
; in DOS mode.".
;
; Portions of this software contains code suggested on
; CBM-Hackers website and Codebase 64.
;
; All rights reserved.
;
; This simple stub
; (C)2020-2021 Bartłomiej "Magnetic-Fox" Węgrzyn!

bsout	=$ffd2          ; address of BSOUT procedure.
ptr	=$22            ; pointers for low and high addresses of
ptr2	=$23            ; text - these are in unused space

; The $D030 address is additional C128 VIC register.
; On C64 it always gives $FF value, while on C128 it
; is usually $FC value.

	inc $d030       ; increment $D030 register
	lda $d030       ; load value from $D030 to accumulator
	dec $d030       ; decrement $D030 register
	eor $d030       ; exclusive OR accumulator with value from $D030
	beq ok          ; if accumulator is equal to data, then jump to program
	ldx #<txt0      ; if not, display the text; get high address of text to X
	ldy #>txt0      ; get low address of text to Y register
	
	stx ptr         ; store high address to $22
	sty ptr2        ; store low address to $23
	
	ldy #$00        ; store $00 to Y register
	
t0:	lda (ptr),y     ; load next character to accumulator
	beq end         ; if reached text end, then go to the end
	jsr bsout       ; if not yet, then execute BSOUT to output the text
	iny             ; increment Y register
	jmp t0          ; jump to the beginning of this procedure - string loop

end:    rts             ; stub finished

; string tables below

txt0:   .byte           "THIS PROGRAM MUST BE RUN UNDER",$0d,"COMMODORE 64.",$0d,0

; If Commodore 64 detected:

ok:	
                        ; Code of actual program goes here.
                        ; It had to be something here, at least only RTS to
                        ; finish this program properly.
                        ; If You like to combine this stub with cc65-compiled
                        ; program, You have to set correct compiling address
                        ; of just C program.
                        ; --start-addr must be set to 2131 and the first usable
                        ; instruction here must be under 2143.
                        ; You must include here first correct instruction to
                        ; make the whole program usable and stable.
