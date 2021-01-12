/*
 * motor.c
 *
 * Created: 2021-01-06 13:28:40
 *  Author: matst
 */ 

void motor_init(void)
{
	DDRC |= (1 << 6); // set PC6 (digital pin 5) as output
	TCCR3A |= 0; // Set OC3A (PC6) to be cleared on Compare Match
	//(Channel A)
	TCCR3A |= 0; // Waveform Generation Mode 5, Fast PWM (8-bit)
	TCCR3B |= 0;
	TCCR3B |= 0; // Timer Clock, 16/64 MHz = 1/4 MHz
}

void motor_set_speed(uint8_t speed)
{

}
