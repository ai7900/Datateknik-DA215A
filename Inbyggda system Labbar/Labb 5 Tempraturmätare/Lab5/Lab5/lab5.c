/*
 * lab5.c
 *
 * Created: 1/5/2021 1:33:22 PM
 *  Author: Mattias Ståhlberg & Johan Fritiofsson
 */ 

#include <xc.h>
#include "hmi/hmi.h"
#include "lcd/lcd.h"
#include "delay/delay.h"
#include "common.h"
#include "temp/temp.h"

enum state 
{
	SHOW_TEMP_C,
	SHOW_TEMP_F,
	SHOW_TEMP_CF,
};

typedef enum state state_t;

int main(void)
{
	hmi_init();
	numkey_init();
	temp_init();
	
	char key; 
	
	state_t currentState = SHOW_TEMP_C;
	state_t nextState = SHOW_TEMP_C;
	

	
    while(1)
    {
        switch (currentState)
        {
	        case SHOW_TEMP_C:
			output_msg("Visar C", "noob",0);
		
	        break;
			case SHOW_TEMP_F:
			//output_msg("Visar F", "noob",0);
			break;
			case SHOW_TEMP_CF:
			//output_msg("Visar CF", "noob",0);
			break;

        }
	
    }
}