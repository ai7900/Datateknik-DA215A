;
; Lab3.asm
;
; Created: 2020-12-04 09:50:00
; Author : Johan Fritiofsson, Mattias Ståhlberg
;


;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000
	.EQU PM_START	= 0x0056
	.EQU NO_KEY		= 0x0F
	.EQU CONVERT	= 0x30
	.DEF TEMP		= R16
	.DEF RVAL		= R24
	.DEF LVAL		= R17
	

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET
	RJMP init

	.ORG PM_START
	.INCLUDE "keyboard.inc"
	.INCLUDE "delay.inc"
	.INCLUDE "lcd.inc"
	
;==============================================================================
; Basic initializations of stack pointer, I/O pins, etc.
;==============================================================================
init:
	; Set stack pointer to point at the end of RAM.
	LDI R16, LOW(RAMEND)
	OUT SPL, R16
	LDI R16, HIGH(RAMEND)
	OUT SPH, R16
	; Initialize pins
	CALL init_pins
	CALL lcd_init
	; Jump to main part of program
	RJMP main

;==============================================================================
; Initialize I/O pins
;==============================================================================
init_pins:	

	LDI TEMP, 0xFF ; SET TEMP TO HIGH
	OUT DDRF, TEMP ;PORT F OUTPUT
	OUT DDRB, TEMP ;PORT B OUTPUT
	OUT DDRD, TEMP ;PORT D OUTPUT

	LDI TEMP, 0x00 ; SET TEMP TO LOW
	OUT DDRE, TEMP ; PORT E INPUT

	RET

;==============================================================================
; Main part of program
;==============================================================================
main:
	LCD_WRITE_CHAR 'K'
	LCD_WRITE_CHAR 'E'
	LCD_WRITE_CHAR 'Y'
	LCD_WRITE_CHAR ':'
	LCD_INSTRUCTION 0xC0 ; SETS CURSOR TO LINE 1 COL O
key_release:
	LDI LVAL, NO_KEY		; last value is NO_KEY								
loop:																		  
	RCALL read_keyboard												  
	CPI RVAL, NO_KEY														  
	BREQ key_release	; branch to key_relased if return value was NO_KEY	  
	CP RVAL, LVAL															  
	BREQ loop		; If RVAL and LVAL is equal branch to loop				  
	MOV LVAL, RVAL	; Copy our return value to last value
	CPI RVAL, 10	; Compare RVAL to 10
	BRLO write		; IF RVAL is lower than 10 jump to write
	LDI TEMP, 7		; Between 9 and A in ASCII is 7, therefore 7 is added to the number
	ADD RVAL, TEMP
write:
	LDI TEMP, CONVERT
	ADD RVAL, TEMP				; Converting RVAL to ASCII
	LCD_WRITE_REG_CHAR RVAL
	LDI R24, 250
	RCALL delay_ms
	RJMP loop