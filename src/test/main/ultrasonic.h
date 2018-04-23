#ifndef ultrasonic_H
#define ultrasonic_H

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

uint16_t distanceL, distanceF, distanceR;
uint8_t flags; // storing zeros until flag is turned on

void init_ultrasonic();

void distanceLeft();
void distanceFront();
void distanceRight();
void distanceUpperFront();

#endif // ultrasonic_H
