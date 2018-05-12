#ifndef ultrasonic_H
#define ultrasonic_H

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_ultrasonic();

uint16_t distanceLeft();
uint16_t distanceFront1();
uint16_t distanceFront2();
uint16_t distanceRight();
uint16_t distanceUpperFront();

#endif // ultrasonic_H
