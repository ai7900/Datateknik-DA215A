/*
 * dice.inc
 *
 *  Created: 2020-12-08 17:25:15
 *   Author: maste
 */ 

;==============================================================================
; Definitions of registers, etc. ("constants")
;==============================================================================
	.EQU ROLL_KEY	= '2'

;==============================================================================
; roll_dice:
; Starts the dice throw. Once ROLL_KEY is relased returns to main program.
; REGISTERS IN USE
; R16 - output
;==============================================================================
roll_dice:
	LDI R16, 6				;dice have 6 values
	
test: 
	NOP
	NOP
	RCALL read_keyboard		;key-value in RVAL
	RCALL key_convert
	CPI RVAL, ROLL_KEY
	BREQ roll				;yes, key 2 is still pressed
	RCALL store_stat
	RET						;no, key is released
roll:
	DEC R16					;start cycle count here
	BREQ roll_dice			;R16 is zero?, start agn at 6
	RJMP test				;no, keep rolling
	
