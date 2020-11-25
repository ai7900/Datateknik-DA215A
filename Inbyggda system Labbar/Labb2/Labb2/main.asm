/*
 * lab1.asm
 * 
 * This is a very simple demo program made for the course DA215A at
 * Malmö University. The purpose of this program is:
 *	-	To test if a program can be transferred to the ATmega32U4
 *		microcontroller.
 *	-	To provide a base for further programming in "Laboration 1".
 *
 * After a successful transfer of the program, while the program is
 * running, the embedded LED on the Arduino board should be turned on.
 * The LED is connected to the D13 pin (PORTC, bit 7).
 *
 * Author:	Mathias Beckius
 *
 * Date:	2014-11-05
 *
 */ 
/*  Johan Fritiofsson
  Mattias Ståhlberg

  This program reads input form a 4 bit keyboard.
  Only 3 bits are used from the keyboard.
  Values between 0-11 can be displayed binary on the display.
  
  */


;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000
	.EQU PM_START	= 0x0056
	.EQU NO_KEY		= 0x0F
	.DEF TEMP		= R16
	.DEF RVAL		= R24
	

;==============================================================================
; Start of program
;==============================================================================
	.CSEG
	.ORG RESET
	RJMP init

	.ORG PM_START
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

	/*LDI R16, 0x80  ; BINARY b10000000 TO HEX
	OUT DDRC, R16*/

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
	LCD_WRITE_CHAR 'H'
	LCD_WRITE_CHAR 'D'
	LCD_WRITE_CHAR 'Q'
	LCD_WRITE_CHAR 'L'
	LCD_WRITE_CHAR 'A'
	LCD_WRITE_CHAR '!'
	/*LDI R24, 'H'
	RCALL lcd_write_chr
	LDI R24, 'E'
	RCALL lcd_write_chr
	LDI R24, 'L'
	RCALL lcd_write_chr
	LDI R24, 'L'
	RCALL lcd_write_chr
	LDI R24, 'O'
	RCALL lcd_write_chr
	LDI R24, '!'
	RCALL lcd_write_chr*/
loop:
	RJMP loop	

/*	CALL read_keyboard

	; LOGICAL SHIFT LEFT 1BIT X4
	LSL RVAL  
	LSL RVAL
	LSL RVAL
	LSL RVAL
	; RETRUN VALUE TO PORT F
	OUT PORTF, RVAL
	NOP
	NOP

	RJMP main			; JUMP TO MAIN

read_keyboard:
	LDI R18, NO_KEY       ; reset counter	
scan_key:
	MOV R19, R18
	; LOGICAL SHIFT LEFT X4
	LSL R19
	LSL R19
	LSL R19
	LSL R19

	OUT PORTB, R19         ; set column and row
	; 13 NOP NECCESARY SINCE 4051 SIGNAL TO ADDRESS MAX TIME 720 ns (1 NOP = 62,5 ns)
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
	NOP

	SBIC PINE, 6 ; SKIP BIT IF IO REG IS CLEAR (IF PINE.6 = 0 SKIP NEXT INSTRUCTION)
	RJMP return_key_val
	INC R18	; INCREMENT
	CPI R18, 12 ; COMPARE INTERMEDIATE (IF	R18 == 12)
	BRNE scan_key	; BRANC NOT EQUAL JUMP scan_key
	LDI R18, NO_KEY        ; no key was pressed!
return_key_val:
	MOV RVAL, R18		; COPY FROM R18 TO RVAL
	RET*/