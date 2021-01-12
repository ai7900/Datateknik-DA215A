/*
 * motor.h
 * This is the device driver for the for a fan.
 * Created: 2021-01-06 13:28:57
 *   Author: Mattias Ståhlberg, Johan Fritiofsson
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

#include <inttypes.h>

void motor_init(void);
void motor_set_speed(uint8_t speed);

#endif /* MOTOR_H_ */