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
	.INCLUDE "delay.inc"
	.INCLUDE "lcd.inc"
	.INCLUDE "keyboard.inc"
	.INCLUDE "dicestrings.inc"
	.INCLUDE "dice.inc"
	.INCLUDE "stats.inc"
	.INCLUDE "monitor.inc"
	.INCLUDE "stat_data.inc"

	
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
	CALL init_stat
	CALL init_monitor
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
	PRINTSTRING Dice_start
	DELAY_1S
again:
	RCALL lcd_clear_display  
	
	PRINTSTRING Dice_2
	
				
loop:																		  
	RCALL read_keyboard	
	RCALL key_compare	
	CPI RVAL, '2'			; if input is 2
	BREQ roll_dice_prep
	CPI RVAL, '3'			; if input is 3
	BREQ show_stats				
	CPI RVAL, '8'			; if input is 8
	BREQ clear_stats	
	CPI RVAL, '9'			; if input is 8
	BREQ go_monitor						  
	//LCD_WRITE_REG_CHAR RVAL
	LDI R24, 250
	RCALL delay_ms
	RJMP loop

roll_dice_prep:
	RCALL lcd_clear_display 
	LDI R24, 40
	RCALL delay_ms
	PRINTSTRING Dice_roll
	RCALL roll_dice
	PUSH R16				; store value from roll_dice on stack
	RCALL lcd_clear_display
	LDI R24, 40
	RCALL delay_ms
	PRINTSTRING dice_value ; prints value to lcd
	POP R16					; get value from stack
	MOV RVAL, R16
	LDI R16, CONVERT
	ADD RVAL, R16
	RCALL lcd_write_chr
	DELAY_1S
	RJMP again

show_stats:

	RCALL showstat
	RJMP again

clear_stats:
	RCALL clearstat
	RJMP again

go_monitor:
	RCALL monitor
	RJMP again