#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"
//#include "PWM.h"

int main(){
  init_motors();
  init_ultrasonic();
  //int decision, prevDecision = 0, turnCount = 0;
  
  uint8_t distanceL = 0x00; uint8_t distanceF = 0x00; uint8_t distanceR = 0x00; uint8_t distanceUF = 0x00; 

  //if(distanceL < distanceR) {decision = 1;}
  //else {decision = 2;}
  
  while(1) {
		distanceL = distanceLeft();
		distanceR = distanceRight();
		distanceF = distanceFront();
		distanceUF = distanceUpperFront();
		
		if(distanceL < 10){PORTB |= (1 << PB7);}
		else{PORTB &= ~(1 << PB7);}
    //=====================================
		if (distanceF < 10){PORTD |= (1 << PD5);}
		else{PORTD &= ~(1 << PD5);}
    //====================================
		if (distanceUF < 10){PORTD |= (1 << PD7);}
		else{PORTD &= ~(1 << PD7);}
	//=====================================
		if (distanceR < 10){PORTD |= (1 << PD6);}
		else{PORTD &= ~(1 << PD6);}
	//=====================================
   
  }
  return 0;
}
