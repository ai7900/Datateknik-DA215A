/*
 * lab5.c
 *	This program is used to read the temperature from a LM35 sensor and show it to an LCD screen in either celcius or farenheit or both.
 *  Created: 1/5/2021 1:33:22 PM
 *  Author: Mattias St�hlberg & Johan Fritiofsson
 
 Date:	2021-01-12
 */ 

#include <xc.h>
#include <stdio.h>
#include "hmi/hmi.h"
#include "lcd/lcd.h"
#include "delay/delay.h"
#include "common.h"
#include "temp/temp.h"
#include "numkey/numkey.h"

	
enum state 
{
	SHOW_TEMP_C,
	SHOW_TEMP_F,
	SHOW_TEMP_CF,
};

typedef enum state state_t;

int main(void)
{
	// Initializations 
	hmi_init();
	numkey_init();
	temp_init();
	
	char key;
	char temp_str[17]; 
	
	state_t currentState = SHOW_TEMP_C;
	state_t nextState = SHOW_TEMP_C;
	

	// Main program
    while(1)
    {
        switch (currentState)
        {
	        case SHOW_TEMP_C:
			sprintf(temp_str,"%u%cC",temp_read_celsius(),0xDF);
			
		
	        break;
			case SHOW_TEMP_F:
			sprintf(temp_str,"%u%cF",temp_read_fahrenheit(),0xDF);
			
			
			break;
			case SHOW_TEMP_CF:
			sprintf(temp_str,"%u%cC, %u%cF",temp_read_celsius(),0xDF,temp_read_fahrenheit(),0xDF);
			

			break;

        }
		output_msg("TEMPERATURE:", temp_str,0);
			
			key = numkey_read();
			switch (key)
			{
				case '1':
				nextState = SHOW_TEMP_C;
				break;
				case '2':
				nextState = SHOW_TEMP_F;
				break;
				case '3':
				nextState = SHOW_TEMP_CF;
				break;
				case NO_KEY:
				break;
				default:
				
				break;
			}
			
		
		currentState = nextState;
	
    }
}