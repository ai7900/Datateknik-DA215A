/*
 * main.c
 * This is a program runs a fan and shows stats about current settings about it. What the current state is and power.
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
#include "motor/motor.h"

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
char mode_str[17];
char reg_str[17];


int main(void)
{
	init();
	motor_init();
	
    while(1)
    {
		
		key = numkey_read();
        switch(currentState)
		{
			///////////MOTOR ON/////////////
			case MOTOR_ON:
			if (regulator_read_power() > 0)
			{
				nextState = MOTOR_RUNNING;
			}
			else if (key == '1')
			{
				nextState = MOTOR_OFF;
			}
			sprintf(mode_str, "MOTOR ON");
			break;
			////////////MOTOR OFF/////////////
			case MOTOR_OFF:
				if(key == '2' && regulator_read_power() == 0)
				nextState = MOTOR_ON;
				sprintf(mode_str, "MOTOR OFF");
				motor_set_speed(0);
			break;
			////////////MOTOR RUNNING/////////////
			case MOTOR_RUNNING:
			motor_set_speed(regulator_read_power());
			if (key == '1')
			nextState= MOTOR_OFF;
			sprintf(mode_str, "MOTOR RUNNING");
			break;
		}
		sprintf(reg_str,"%u%c",regulator_read_power(), '%');
		output_msg(mode_str,reg_str,0);
		currentState = nextState;
    }
}

int init()
{
	hmi_init();
	numkey_init();
	regulator_init();
}