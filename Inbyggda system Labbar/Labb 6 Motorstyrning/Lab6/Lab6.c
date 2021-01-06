/*
 * main.c
 *
 * Created: 1/6/2021 11:38:59 AM
 *  Author: Mattias Ståhlberg, Johan Fritiofsson
 */ 

#include <xc.h>
#include <stdio.h>
#include "delay/delay.h"
#include "hmi/hmi.h"
#include "lcd/lcd.h"
#include "numkey/numkey.h"
#include "regulator/regulator.h"
#include "common.h"

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
		
		key = numkey_read();
        switch(currentState)
		{
			case MOTOR_ON:
			if (regulator_read_power() > 0)
			{
				nextState = MOTOR_RUNNING;
			}
			else if (key == '1')
			{
				nextState = MOTOR_OFF;
			}
			output_msg("MOTOR ON","INSER POWER HERE", 0); // TODO:
			break;
			
			case MOTOR_OFF:
				if(key == '2' && regulator_read_power() == 0)
				nextState = MOTOR_ON;
				output_msg("MOTOR OFF","",0);
			break;
			
			case MOTOR_RUNNING:
			
			if (key == '1')
			nextState= MOTOR_OFF;
			
			output_msg("MOTOR RUNNING", "INSERT POWER HERE",0); // TODO:
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