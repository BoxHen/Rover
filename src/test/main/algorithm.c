#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"

void algorithm(){
  init_motors();
  init_ultrasonic();
  int decision, prevDecision, turnCount = 0;

  if(distanceL < distanceR) {decision = 1;}
  else {decision = 2;}

  while(1) {
		distanceLeft();
		distanceRight();
		distanceFront();

    switch(decision){
      case 1:// left wall is closer
          turnLeft(); _delay_ms(1050);
          prevDecision = 1; // used to alternate between turns for going up and turn maze
          turnCount++;
          if(turnCount >= 3){decision = 6} // this will execute the updown traversal after we get to top left corner
          else {decision = 5;}
          break;
      case 2: // right wall is closer
          turnRight(); _delay_ms(1050);
          prevDecision = 2; // used to alternate between turns for going up and turn maze
          turnCount++;
          if(turnCount >= 3){decision = 7} // this will execute the updown traversal after we get to top right corner
          else {decision = 5;}
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
          decision = 5;};
          break;
      case 4: // obstacle turn right
          turnLeft(); _delay_ms(1050);
          while(distanceL <= 15){ forward(); } // move forward if you are against the wall of the obstacle
          turnRight(); _delay_ms(1050);
          while(distanceR >= 15){ forward(); } // after turn we will not be aginst the wall. move forward until you are
          while(distanceR <= 15){ forward(); } // move forward if you are against the wall of the obstacle
          turnRight(); _delay_ms(1050);
          while(distanceF >= 10){ forward(); } // move forward until front sensor sees a wall
          turnLeft(); _delay_ms(1050);
          decision = 5;};
          break;
      case 5: // move forward until we see a obstacle or wall
          while( distanceF >= 10 ){
            forward(); _delay_ms(100); // used so motors move or else it loops to fast for motors to process
          }
          if     ( distanceUF >= 10 && distanceL <= 10 ){decision = 3; break;} // obstacle avoid case left
          else if( distanceUF >= 10 && distanceR <= 10 ){decision = 4; break;} // obstacle avoid right
          else if( distanceF <= 10 && distanceL <= 10 ){decision = 2;  break;} // corner turn case for left
          else if( distanceF <= 10 && distanceR <= 10 ){decision = 1;  break;} //corner turn right
          else if( prevDecision == 1 ) {decision = 2; break;}
          else decision = 1; break;
      case 6: // up/dowm motion from left corner
          //prevDecision = 6; // used to alternate between turns for going up and turn maze
          forward(); _delay_ms(400); // test this delay
          turnRight(); _delay_ms(1050);
          decision = 5;
      case 7: // up/down motion from right corner
          //prevDecision = 7; // used to alternate between turns for going up and turn maze
          forward(); _delay_ms(400); // test this delay
          turnLeft(); _delay_ms(1050);
          decision = 5;


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
