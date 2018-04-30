#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"

void algorithm(){
  init_motors();
  init_ultrasonic();
  int decision, prev_decision;

  if(distanceL < distanceR) {decision = 1;}
  else {decision = 2;}

  while(1) {
		distanceLeft();
		distanceRight();
		distanceFront();

    switch(decision){
      case 1:// left wall is closer
          prev_decision = decision;
          turnLeft(); _delay_ms(1050);
          while( distanceF >= 10 ){
            forward(); _delay_ms(100); // used so motors move or else it loops to fast for motors to process
          }
          if(distanceUF >= 10){decision = 3;} // obstacle avoid case
          else {decision = *********;} // corner turn case
          break;
      case 2: // right wall is closer
          prev_decision = decision;
          turnRight(); _delay_ms(1050);
          while( distanceF >= 10 ){
            forward(); _delay_ms(100); // used so motors move or else it loops to fast for motors to process
          }
          if(distanceUF >= 10){decision = 4;} // obstacle avoid case
          else {decision = *********;};} // corner turn case
          break;
      case 3: // obstacle turn for left wall start
          turnRight(); _delay_ms(1050);
          while(distanceL <= 15){ forward(); } // move forward if you are against the wall of the obstacle
          turnLeft(); _delay_ms(1050);
          while(distanceL >= 15){ forward(); } // after turn we will not be aginst the wall. move forward until you are
          while(distanceL <= 15){ forward(); } // move forward if you are against the wall of the obstacle
          turnLeft(); _delay_ms(1050);
          while(distanceF >= 10){ forward(); } // move forward until front sensor sees a wall
          turnRight(); _delay_ms(1050);
          decision = *********;};
          break;
      case 4:
          turnLeft(); _delay_ms(1050);
          while(distanceL <= 15){ forward(); } // move forward if you are against the wall of the obstacle
          turnRight(); _delay_ms(1050);
          while(distanceR >= 15){ forward(); } // after turn we will not be aginst the wall. move forward until you are
          while(distanceR <= 15){ forward(); } // move forward if you are against the wall of the obstacle
          turnRight(); _delay_ms(1050);
          while(distanceF >= 10){ forward(); } // move forward until front sensor sees a wall
          turnLeft(); _delay_ms(1050);
          decision = *********;};
          break;

    }


    /*if(distanceL < distanceR){ // go to left wall since it is closer
      //turnLeft(); // make this a 90deg turn - we will need encoders to do this
        turnLeft();
		    _delay_ms(1050);
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
*/
    return 0;
  }
}
