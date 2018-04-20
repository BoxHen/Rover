#ifndef ultrasonic_H
#define ultrasonic_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

uint16_t distance, distance2;
uint8_t flags; // storing zeros until flag is turned on

void distanceLeft();
void distanceFront();
void distanceRight();

#endif // ultrasonic_H
