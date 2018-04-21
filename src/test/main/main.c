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
			PORTB |= (1 << PB5);
			leftmotor_foward();
			rightmotor_foward();
		}else{
			PORTB &= ~(1 << PB5);
			brake();
		}
        //=====================================    
		if (distanceF < 10){
			PORTC |= (1 << PC1);
			
			//leftmotor_foward();
			//rightmotor_foward();
		}else{
			PORTC &= ~(1 << PC1);
		}
		//=====================================
		if (distanceR < 10){
			PORTC |= (1 << PC2);
		}else{
			PORTC &= ~(1 << PC2);
		}
  }
  return 0;
}
