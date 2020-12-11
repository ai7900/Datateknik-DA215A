/*
 * stat_data.inc
 *
 *  Created: 2020-12-11 12:59:23
 *   Author: maste
 */ 

 /* ---------------------------------------------------
Space in the RAM to save the results from dice throws. 
The following functions are provided:

	store_stat	(R24 contains the dice value)

				The function will increment the
				Total number of throws and the
				number of throws with results equals R24.

	get_stat	(R24 gives the value for which the
				result is retrieved. If R24 = 0, the
				total number of throws shall be returned.
				The result is returned in R24.

	clear_stat	(no parameters in nor out)
				Clears all data.
--------------------------------------------------------*/
; REGISTER IN USE:
; R15 - TEMP VARIABLE
; R16 - DICE VALUE
; R24 - RETURN VALUE

	.DSEG				; The following applies to the RAM:
	.ORG	0x100			; Set starting
							; address of data
							; segment to 0x100

stat_total:	.BYTE		7		; <skapa så mycket plats som behövs.
									

	.CSEG
store_stat:		
	LDI XH, HIGH(stat_total)
	LDI XL, LOW(stat_total)
	LD R15, X
	INC R15
	ST X, R15	; INCREASE TOTAL DICE ROLLS, AND STORE IT TO MEMORY

	ADD XL, R16
	LDI R24, 0
	ADC XH, R24
	LD R15,X
	INC R15
	ST X, R15		; INCREASE SPECIFIC DICE ROLL (Nbr1-6)

	RET

get_stat:
	LDI XH, HIGH(stat_total)
	LDI XL, LOW(stat_total)
	ADD XL, RVAL
	LDI RVAL, 0
	ADC XH, RVAL
	LD RVAL, X
			
	RET
clear_stat:    
	LDI R16, 0x00
	STS stat_total, R16
	STS stat_total+1, R16
	STS stat_total+2, R16
	STS stat_total+3, R16
	STS stat_total+4, R16
	STS stat_total+5, R16
	STS stat_total+6, R16
 	RET