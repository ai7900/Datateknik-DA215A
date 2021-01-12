/*
 * temp.h
 *
 * This is the device driver for the LM35 temperature sensor.
 *
 * Author:	Mattias Ståhlberg & Johan Fritiofsson
 *
 * Date:	2021-01-12
 */ 

#ifndef TEMP_H_
#define TEMP_H_

#include <inttypes.h>

void temp_init(void);
uint8_t temp_read_celsius(void);
uint8_t temp_read_fahrenheit(void);

#endif /* TEMP_H_ */