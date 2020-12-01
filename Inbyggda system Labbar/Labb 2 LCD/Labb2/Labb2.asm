
/*
Author: Johan Fritiofsson, Mattias Ståhlberg
Date: 2020-11-26

This Program displays ASCII on an LCD-display.
It can take inputs from a 4bit keyboard and display the HEX numbers between 1-B on the screen as ASCII.
  
*/

/*
Registers in use:
R16 
R18 
R19 
R24
*/




;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU RESET		= 0x0000
	.EQU PM_START	= 0x0056
	.EQU NO_KEY		= 0x0F
	.EQU CONVERT	= 0x30
	.DEF TEMP		= R16
	.DEF RVAL		= R24
	
;==========
; Sends instructions to LCD with a 39 us delay after command.
;=========
	.MACRO LCD_INSTRUCTION
	LDI R24, @0
	RCALL lcd_write_instr
	LDI R24, 39
	RCALL delay_micros
	.ENDMACRO
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

	; ASCII(1) = 0x30 = b00110000 = 48

	LDI R18, 0b00000001
	LDI TEMP, CONVERT
	ADD R18, TEMP

	LCD_WRITE_CHAR 'K'
	LCD_WRITE_CHAR 'E'
	LCD_WRITE_CHAR 'Y'
	LCD_WRITE_CHAR ':'
	LCD_INSTRUCTION 0xC0 ; SETS CURSOR TO LINE 1 COL O
loop:
	RCALL read_keyboard
	CPI RVAL, NO_KEY
	BREQ loop
	CPI RVAL, 10
	BRLO write    ; IF RVAL is lower than 10 jump to write
	LDI TEMP, 7		; Between 9 and A in ASCII is 7, therefore 7 is added to the number
	ADD RVAL, TEMP
write:
	LDI TEMP, CONVERT
	ADD RVAL, TEMP
	LCD_WRITE_REG_CHAR RVAL
	LDI R24, 250
	RCALL delay_ms
	RJMP loop

	

	
read_keyboard:
	LDI R18, 0
scan_key:
	MOV R19, R18
	LSL R19
	LSL R19
	LSL R19
	LSL R19
	
	OUT PORTB, R19
	PUSH R18
	LDI R24, 1
	RCALL delay_ms
	POP R18
	
	SBIC PINE, 6
	RJMP return_key_val
	INC R18

	; Är vi 100% på att delay_ms inte ha påverkat R18 på något konstigt sätt?
	; Enkelt sätt att testa detta på är att hårdkoda in NOP:s som ersätter delay_ms funktionen.
	
	CPI R18, 12
	BRNE scan_key
	LDI R18, NO_KEY        ; no key was pressed!
return_key_val:
	MOV RVAL, R18		; COPY FROM R18 TO RVAL
	RET
			
	
/*
	CALL read_keyboard

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