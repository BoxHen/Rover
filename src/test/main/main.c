#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"

int main(){
  init_ultrasonic();

  while(1) {
		distanceLeft();
		distanceRight();
    distanceFront();

		if (distanceL < 10){
			PORTC |= (1 << PC0);
		}else{
			PORTC &= ~(1 << PC0);
		}

		if (distanceF < 10){
			PORTC |= (1 << PC1);
		}else{
			PORTC &= ~(1 << PC1);
		}
  }
  return 0;
}
