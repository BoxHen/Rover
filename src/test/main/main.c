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
  int decision, prevDecision = 0, turnCount = 0;
  
  uint8_t distanceL = 0x00; uint8_t distanceF = 0x00; uint8_t distanceR = 0x00; uint8_t distanceUF = 0x00; 

  distanceL = distanceLeft();
  distanceR = distanceRight();
  if(distanceL < distanceR) {decision = 1;}
  else {decision = 2;}
  
  while(1) {
		distanceL = distanceLeft();
		distanceR = distanceRight();
		distanceF = distanceFront();
		distanceUF = distanceUpperFront();
		
    switch(decision){
      case 1:// left wall is closer
          turnLeft(); _delay_ms(1050);
		  brake();
		  _delay_ms(100);
          prevDecision = 1; // used to alternate between turns for going up and turn maze
          turnCount++;
          if(turnCount >= 3){decision = 7;} // this will execute the updown traversal after we get to top left corner
          else {decision = 5;}
          break;
      case 2: // right wall is closer
          turnRight(); _delay_ms(1050);
          prevDecision = 2; // used to alternate between turns for going up and turn maze
          turnCount++;
          if(turnCount >= 3){decision = 6;} // this will execute the updown traversal after we get to top right corner
          else {decision = 5;}
          break;
      case 3: // obstacle turn for left wall start
          turnRight(); _delay_ms(1050);
          while(distanceL <= 20){ forward(); distanceL = distanceLeft();} // move forward if you are against the wall of the obstacle
          turnLeft(); _delay_ms(1050);
          while(distanceL >= 20){ forward(); distanceL = distanceLeft();} // after turn we will not be aginst the wall. move forward until you are
          while(distanceL <= 20){ forward(); distanceL = distanceLeft();} // move forward if you are against the wall of the obstacle
          turnLeft(); _delay_ms(1050);
		  distanceF = distanceFront();
          while(distanceF >= 5){ forward(); distanceF = distanceFront();} // move forward until front sensor sees a wall
          turnRight(); _delay_ms(1050);
          decision = 5;
          break;
      case 4: // obstacle turn right
          turnLeft(); _delay_ms(1050);
          while(distanceL <= 20){ forward(); distanceL = distanceLeft();} // move forward if you are against the wall of the obstacle
          turnRight(); _delay_ms(1050);
          while(distanceR >= 20){ forward(); distanceR = distanceRight();} // after turn we will not be aginst the wall. move forward until you are
          while(distanceR <= 20){ forward(); distanceR = distanceRight();} // move forward if you are against the wall of the obstacle
          turnRight(); _delay_ms(1050);
		  distanceF = distanceFront();
          while(distanceF >= 5){ forward(); distanceF = distanceFront();} // move forward until front sensor sees a wall
          turnLeft(); _delay_ms(1050);
          decision = 5;
          break;
      case 5: // move forward until we see a obstacle or wall
		  distanceF = distanceFront();
          while( distanceF >= 10 ){ // fix it smacks into wall
            forward(); _delay_ms(10); brake(); // used so motors move or else it loops to fast for motors to process
			distanceF = distanceFront(); 
          }
          if     ( distanceUF >= 20 && distanceL <= 20 ){decision = 3; break;} // obstacle avoid case left
          else if( distanceUF >= 20 && distanceR <= 20 ){decision = 4; break;} // obstacle avoid right
          else if( distanceF <= 20 && distanceL <= 20 ){decision = 2;  break;} // corner turn case for left
          else if( distanceF <= 20 && distanceR <= 20 ){decision = 1;  break;} //corner turn right
          else if( prevDecision == 1 ) {decision = 2; break;}
          else decision = 1; break;
      case 6: // up/dowm motion from left corner
          //prevDecision = 6; // used to alternate between turns for going up and turn maze
          forward(); _delay_ms(400); // test this delay
          turnRight(); _delay_ms(1050);
          decision = 5;
		  break;
      case 7: // up/down motion from right corner
          //prevDecision = 7; // used to alternate between turns for going up and turn maze
          forward(); _delay_ms(400); // test this delay
          turnLeft(); _delay_ms(1050);
          decision = 5;
		  break;
	  default: brake();
	}
  }
  return 0;
}

