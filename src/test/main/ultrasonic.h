#ifndef ultrasonic_H
#define ultrasonic_H

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_ultrasonic();

uint8_t distanceLeft();
uint8_t distanceFront();
uint8_t distanceRight();
uint8_t distanceUpperFront();

#endif // ultrasonic_H
