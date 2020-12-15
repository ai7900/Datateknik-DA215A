/*
 * This lab assignment is an introduction to C programming for
 * embedded systems. The purpose of this assignment is to learn:
 *	- how to mix C and Assembly code
 *	- how device drivers can be written in C
 *	- how a simple user interface (HMI) can be implemented
 *	- the benefits of following a consistent way of programming
 *	- etc....
 *
 * The final goal of this assignment is to complete a little game
 * called "Guess the number", where the player shall guess a random
 * number between 1-100.
 *
 * Author: Mathias Beckius
 *
 * Date: 2014-12-01
 */

#include "hmi/hmi.h"
#include "random/random.h"
#include "guess_nr.h"
#include "lcd/lcd.h"
#include "delay/delay.h"


int main(void)
{
/*
	uint16_t rnd_nr;
	
	// initialize HMI (LCD and numeric keyboard)
	hmi_init();
	// generate seed for the pseudo-random number generator
	random_seed();
	
	// show start screen for the game
	output_msg("Welcome!", "Let's play...", 3);
	// play game
    while (1) {
		// generate a random number
	    rnd_nr = random_get_nr(100) + 1;
		// play a round...
		play_guess_nr(rnd_nr);
    }
*/


/******************************************************************************
	OVANFÖR FINNS HUVUDPROGRAMMET, DET SKA NI INTE MODIFIERA!
	NEDANFÖR KAN NI SKRIVA ERA TESTER. GLÖM INTE ATT PROGRAMMET MÅSTE HA EN
	OÄNDLIG LOOP I SLUTET!
	
	NÄR DET ÄR DAGS ATT TESTA HUVUDPROGRAMMET KOMMENTERAR NI UT (ELLER RADERAR)
	ER TESTKOD. GLÖM INTE ATT AVKOMMENTERA HUVUDPROGRAMMET
******************************************************************************/

	while (1)
	{
		lcd_set_cursor_mode(CURSOR_BLINK);
		delay_s(2);
		lcd_set_cursor_mode(CURSOR_ON);
		delay_s(2);
		lcd_set_cursor_mode(CURSOR_OFF);
		delay_s(2);
	}
}