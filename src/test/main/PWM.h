#ifndef PWM_H
#define PWM_H

#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>

void PWM_left(uint8_t value);
void PWM_right(uint8_t value);

#endif
