#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"
//#include "PWM.h"
#define delay 1075

uint8_t distL = 0x00; uint8_t distF = 0x00; uint8_t distR = 0x00; uint8_t distUF = 0x00; 

void sensor_update();

int main(){
  init_motors();
  init_ultrasonic();
  int decision, prevDecision = 0, turnCount = 0;
  
  //uint8_t distL = 0x00; uint8_t distF = 0x00; uint8_t distR = 0x00; uint8_t distUF = 0x00; 
  uint8_t wallDist = 20;

  sensor_update();
  if(distL < distR) {decision = 1;}
  else {decision = 2;}
  
  while(1) {
	sensor_update();	
    switch(decision){
      case 1:// left wall is closer
          turnLeft(); _delay_ms(delay); 
				brake();_delay_ms(50);
          prevDecision = 1; // used to alternate between turns for going up and turn maze
          turnCount++;
          if(turnCount >= 3){decision = 7;} // this will execute the updown traversal after we get to top left corner
          else {decision = 5;}
          break;
      case 2: // right wall is closer
          turnRight(); _delay_ms(delay);
				brake();_delay_ms(50);
          prevDecision = 2; // used to alternate between turns for going up and turn maze
          turnCount++;
          if(turnCount >= 3){decision = 6;} // this will execute the updown traversal after we get to top right corner
          else {decision = 5;}
          break;
      case 3: // obstacle turn for left wall start
          turnRight(); _delay_ms(delay); 
				brake();_delay_ms(50);
          while(distL <= 20){ forward(); distL = distanceLeft();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
          turnLeft(); _delay_ms(delay); 
				brake();_delay_ms(50);
          while(distL >= 20){ forward(); distL = distanceLeft();} // after turn we will not be aginst the wall. move forward until you are
				brake();_delay_ms(50);
          while(distL <= 20){ forward(); distL = distanceLeft();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
          turnLeft(); _delay_ms(delay);
				brake();_delay_ms(50);
		  distF = distanceFront();
          while(distF >= 5){ forward(); distF = distanceFront();} // move forward until front sensor sees a wall
				brake();_delay_ms(50);
          turnRight(); _delay_ms(delay);
				brake();_delay_ms(50);
          decision = 5;
          break;
      case 4: // obstacle turn right
          turnLeft(); _delay_ms(delay);
				brake();_delay_ms(50);
          while(distL <= 20){ forward(); distL = distanceLeft();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
          turnRight(); _delay_ms(delay);
				brake();_delay_ms(50);
          while(distR >= 20){ forward(); distR = distanceRight();} // after turn we will not be aginst the wall. move forward until you are
				brake();_delay_ms(50);
          while(distR <= 20){ forward(); distR = distanceRight();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
          turnRight(); _delay_ms(delay);
				brake();_delay_ms(50);
		  distF = distanceFront();
          while(distF >= 5){ forward(); distF = distanceFront();} // move forward until front sensor sees a wall
				brake();_delay_ms(50);
          turnLeft(); _delay_ms(delay);
				brake();_delay_ms(50);
          decision = 5;
          break;
      case 5: // move forward until we see a obstacle or wall
		  //distF = distanceFront();
          while( distF >= 12 ){ 
            forward(); _delay_ms(10);  // used so motors move or else it loops to fast for motors to process
			distF = distanceFront(); 
          }
				brake();_delay_ms(50);
		  sensor_update();
          if     ( distF <= 15 && distUF >= 15 && distL <= 20 ){decision = 3; break;} // obstacle avoid case left
          else if( distF <= 15 && distUF >= 15 && distR <= 20 ){decision = 4; break;} // obstacle avoid right
          else if( distF <= 15 && distL <= (wallDist) ){decision = 2;  break;} // corner turn case for left
          else if( distF <= 15 && distR <= (wallDist) ){decision = 1;  break;} //corner turn right // fix this breaks down in the cneter of the mze !!!!!
          else if( prevDecision == 1 ) {decision = 2; break;}
          else decision = 1; break;
      case 6: // up/dowm motion from left corner
          //prevDecision = 6; // used to alternate between turns for going up and turn maze
          forward(); _delay_ms(500);  // test this delay
				brake();_delay_ms(50);
          turnRight(); _delay_ms(delay); 
				brake();_delay_ms(50);
		  //wallDist += 15; 
          decision = 5;
		  break;
      case 7: // up/down motion from right corner
          //prevDecision = 7; // used to alternate between turns for going up and turn maze
          forward(); _delay_ms(500); // test this delay
				brake();_delay_ms(50);
          turnLeft(); _delay_ms(delay); 
				brake();_delay_ms(50);
		  //wallDist += 15; 
          decision = 5;
		  break;
	  //default: brake();
	}
  }
  return 0;
}
void sensor_update(){
	distL = distanceLeft();
	distR = distanceRight();
	distF = distanceFront();
	distUF = distanceUpperFront();
}

