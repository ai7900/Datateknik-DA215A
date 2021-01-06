/*
 * main.c
 *
 * Created: 1/6/2021 11:38:59 AM
 *  Author: Mattias Ståhlberg, Johan Fritiofsson
 */ 

#include <xc.h>
#include "delay/delay.h"
#include "hmi/hmi.h"
#include "lcd/lcd.h"
#include "numkey/numkey.h"
#include "regulator/regulator.h"

enum state
{
	MOTOR_ON,
	MOTOR_OFF,
	MOTOR_RUNNING,
};

typedef enum state state_t;

state_t currentState = MOTOR_OFF;
state_t nextState = MOTOR_OFF;

char key;


int main(void)
{
	init();
	
    while(1)
    {
        switch(currentState)
		{
			case MOTOR_ON:
			break;
			
			case MOTOR_OFF:
				key = numkey_read();
				if(key == '2' && regulator_read_power() == 0)
				nextState = MOTOR_ON;
			break;
			
			case MOTOR_RUNNING:
			break;
		}
		
		currentState = nextState;
    }
}

void init(void)
{
	hmi_init();
	numkey_init();
	regulator_init();
}