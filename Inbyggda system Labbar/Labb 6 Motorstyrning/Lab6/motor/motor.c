/*
 * motor.c
 * This is the device driver for the for a fan.
 * Created: 2021-01-06 13:28:40
 *   Author: Mattias Ståhlberg, Johan Fritiofsson
 */ 

#include <avr/io.h>

void motor_init(void)
{
	DDRC |= (1 << 6); // set PC6 (digital pin 5) as output
	TCCR3A |= (1 << COM3A1)  ; // Set OC3A (PC6) to be cleared on Compare Match
								//(Channel A)
	TCCR3A |=   (1<<WGM30)  ; // Waveform Generation Mode 5, Fast PWM (8-bit)
	TCCR3B |=	(1<<WGM32);
	TCCR3B |=	(1<<CS31) | (1<<CS30); // Timer Clock, 16/64 MHz = 1/4 MHz
}

void motor_set_speed(uint8_t speed)
{
	OCR3AH = 0;
	OCR3AL = (speed *255) / 100;
}
