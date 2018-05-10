#ifndef algorithm_H
#define algorithm_H

#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"
#define delay 1100

#define delay 1100

uint16_t objToEdgeCnt = 0, objToEdgeRead = 0;

void sensor_update(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR, uint8_t distUF);
void obstLeftAvoid(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR);
void obstRightAvoid(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR);
void reAdjustFront(uint8_t distF1, uint8_t distF2);

#endif