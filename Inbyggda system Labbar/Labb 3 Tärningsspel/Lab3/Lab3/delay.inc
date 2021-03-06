/*
 * delay.inc
 *
 * Author:	Mattias St�hlberg & Johan Fritiofsson
 *
 * Date:	2020-11-25
 *
 * Diffent kinds of delays through macros and subroutines
 * REGISTERS IN USE
 *	R18
 *	R24
 */
  

;==============================================================================
; Delay 1 second
;==============================================================================
	.MACRO DELAY_1S
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	LDI R24, 250
	RCALL delay_ms
	.ENDMACRO


;==============================================================================
; Delay of 1 �s (including RCALL)
;==============================================================================
delay_1_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	; 6 NOP:s reqired for 16MHz 1�s highs and lows.
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	RET

;==============================================================================
; Delay of X �s
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_micros:   /* UPPGIFT: komplettera med ett antal NOP-instruktioner!!! */
	; 12 NOP:s works good for longer times (>3�s)
        ; The first and last instructs only run 1 time, so you can exlude them from the equation.
        ; DEC + CPI + BRNE(false) + nNOP = 2 + 1 + 1 + n = 16.
        ; n = 12  => we need 12 NOP:s for longer times.
    ; 3 NOP:s work good for shorter times (1-3�s)
    ; See generated time graph for microseconds in exel
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	DEC R24
	CPI R24, 0			; more loops to do?
	BRNE delay_micros	;	continue!
	RET

;==============================================================================
; Delay of X ms
;	LDI + RCALL = 4 cycles
;==============================================================================
delay_ms:
	MOV R18, R24
loop_dms:
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	LDI R24, 250
	RCALL delay_micros
	DEC R18
	CPI R18, 0			; more loops to do?
	BRNE loop_dms		;	continue!
	RET