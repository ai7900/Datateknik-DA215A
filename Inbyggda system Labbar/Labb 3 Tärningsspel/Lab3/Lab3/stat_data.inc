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

	.DSEG				; The following applies to the RAM:
	.ORG	0x100			; Set starting
							; address of data
							; segment to 0x100

//<your_label>:	.BYTE		<n>		; <skapa så mycket plats som behövs.
									;Antag att max värde per lagrad variabel är 255>
	.CSEG
store_stat:		;<skriv kod för rutinen>
	RET
get_stat:		;<skriv kod för rutinen>
	RET
clear_stat:     ;<skriv kod för rutinen>
	RET