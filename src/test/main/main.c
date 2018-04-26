#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"

int main(){
  init_motors();
  init_ultrasonic();

  while(1) {
		distanceLeft();
		distanceRight();
		distanceFront();

		if (distanceL < 10){
			PORTB |= (1 << PB6);
			leftmotor_foward();
			rightmotor_foward();
		}else{
			PORTB &= ~(1 << PB6);
			brake();
		}
    //=====================================
		if (distanceF < 10){
			PORTB |= (1 << PB7);
      leftmotor_reverse();
      rightmotor_reverse();
		}else{
			PORTB &= ~(1 << PB7);
      brake();
		}
		//=====================================
		if (distanceR < 10){
			PORTD |= (1 << PD5);
      turnLeft();
		}else{
			PORTD &= ~(1 << PD5);
      brake();
		}
    //====================================
    if (distanceUF < 10){
			PORTD |= (1 << PD6);
      turnRight();
		}else{
			PORTD &= ~(1 << PD6);
		}
  }
  return 0;
}
