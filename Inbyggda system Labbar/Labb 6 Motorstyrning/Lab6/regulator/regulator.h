/*
 * temp.h
 *
 * This is the device driver for the for a potentiometer.
 *
 *  Author: Mattias Ståhlberg, Johan Fritiofsson
 *
 * Date:	2014-12-07
 */ 

#ifndef TEMP_H_
#define TEMP_H_

#include <inttypes.h>

void regulator_init(void);
uint8_t regulator_read_power(void);

#endif /* TEMP_H_ */