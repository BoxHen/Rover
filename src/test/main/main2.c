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
  
  //uint8_t distanceL = 0x00; uint8_t distanceF = 0x00; uint8_t distanceR = 0x00; uint8_t distanceUF = 0x00; 
uint8_t distanceL = 0x00;
uint8_t distanceR = 0x00;
uint8_t distanceF = 0x09;
uint8_t distanceUF = 0x00; 
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
  /*while(1){
		rightmotor_foward();
		leftmotor_reverse();
		_delay_ms(5);
		distanceL = distanceLeft();  // check sensors
		distanceR = distanceRight(); // check sensors
		if( (distanceL == distanceR) | (distanceL-2 <= distanceR < distanceL) | (distanceL <= distanceR < distanceL+2) ){break;} 
  }
  brake();*/
  /*turnRight(); _delay_ms(1050);
          while(distanceL <= 20){ forward(); distanceL = distanceLeft();} // move forward if you are against the wall of the obstacle
          turnLeft(); _delay_ms(1050);
          while(distanceL >= 20){ forward(); distanceL = distanceLeft();} // after turn we will not be aginst the wall. move forward until you are
          while(distanceL <= 20){ forward(); distanceL = distanceLeft();} // move forward if you are against the wall of the obstacle
          turnLeft(); _delay_ms(1050);
          while(distanceF >= 5){ forward(); distanceF = distanceFront();} // move forward until front sensor sees a wall
          turnRight(); _delay_ms(1050);
		  forward();
  return 0;*/
  //}

