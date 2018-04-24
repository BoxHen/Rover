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

    if(distanceL < distanceR){ // go to left wall since it is closer
      //turnLeft(); // make this a 90deg turn - we will need encoders to do this
      while(1){
        turnLeft();
        if(distanceL<10) break;
      }
      while(1){
        forward();
        if(distanceF<5 && distanceUpperFront>5){
          turnRight();
          if(distanceL<5) forward();
          turnLeft();
          if(distanceL<5) forward();
          turnLeft();
          if(distanceL<5 && distanceF>5) forward();
          turnRight();
        }
        if(distanceL<5 && distanceFront<5 && distanceUpperFront<5) break; // get to corner
      }
    }else{ // go to right wall since it is closer
      turnRight();
    }

	// 	if (distanceL < 10){
	// 		PORTB |= (1 << PB5);
	// 		leftmotor_foward();
	// 		rightmotor_foward();
	// 	}else{
	// 		PORTB &= ~(1 << PB5);
	// 		brake();
	// 	}
  //   //=====================================
	// 	if (distanceF < 10){
	// 		PORTC |= (1 << PC1);
  //
	// 		//leftmotor_foward();
	// 		//rightmotor_foward();
	// 	}else{
	// 		PORTC &= ~(1 << PC1);
	// 	}
	// 	//=====================================
	// 	if (distanceR < 10){
	// 		PORTC |= (1 << PC2);
	// 	}else{
	// 		PORTC &= ~(1 << PC2);
	// 	}
  // }
  return 0;
}
