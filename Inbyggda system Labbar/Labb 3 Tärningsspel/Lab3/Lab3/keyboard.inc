/*
 * keyboard.inc
 * This file contians a subrutine for reading binary inputs from from a 4-bit keyboard 0-B
 * Registers in use:
 *  -Internal: R18, R19 
 *  -Output: R24  
 *  Created: 2020-12-04 09:54:59
 *   Author: Johan Fritiofsson, Mattias Ståhlberg
 */ 


;-----------------------------------------------------------------
 read_keyboard:
; Parameters none
; R18: loop through 0-12.
; OUT: R24: contains binary value from keyboard.
; Limitations: If no input NO_KEY is returned.
;----------------------------------------------------------------read_keyboard:
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
	RCALL delay_ms ; delay for bounce
	POP R18
	
	SBIC PINE, 6
	RJMP return_key_val
	INC R18	
	CPI R18, 12
	BRNE scan_key
	LDI R18, NO_KEY        ; no key was pressed!
return_key_val:
	MOV RVAL, R18		; COPY FROM R18 TO RVAL
	RET
