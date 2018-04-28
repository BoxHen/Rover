#ifndef PWM_H
#define PWM_H

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void init_PWM();

void PWM_leftA(uint8_t value);
void PWM_rightA(uint8_t value);
void PWM_leftB(uint8_t value);
void PWM_rightB(uint8_t value);

#endif
