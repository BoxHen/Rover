#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "algorithm.h"
#include "motors.h"

uint16_t distL = 0x0000; uint16_t distF1 = 0x0000; uint16_t distF2 = 0x0000; uint16_t distR = 0x0000; uint16_t distUF = 0x0000; 
	
int main(){
  init_motors();
  init_ultrasonic();
  uint8_t turnCount = 0x00;
  int decision = 1, delayCount = 0, prevDecision = 0;
  
  //uint8_t distL = 0x00; uint8_t distF = 0x00; uint8_t distR = 0x00; uint8_t distUF = 0x00; 

  sensor_update(distL, distF1, distF2, distR, distUF); 
  if(distL < distR) {decision = 1;}
  else {decision = 2;}
  
  while(1) {
    sensor_update(distL, distF1, distF2, distR, distUF); 	
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
		  obstLeftAvoid(distL, distF1, distF2, distR);
          decision = 5;
          break;
      case 4: // obstacle turn right
          obstRightAvoid(distL, distF1, distF2, distR);
          decision = 5;
          break;
      case 5: // move forward until we see a obstacle or wall
          sensor_update(distL, distF1, distF2, distR, distUF); 
          while( (distF1 >= 754)&&(distF2 >= 754) ){ 
            forward(); //_delay_ms(150); brake(); _delay_ms(10); // used so motors move or else it loops to fast for motors to process
			distF1 = distanceFront1(); distF2 = distanceFront2();
          }
          brake();
				
          reAdjustFrontL(distL, distF1, distF2, distR, distUF);
	  reAdjustFrontR(distL, distF1, distF2, distR, distUF);
          brake();
          sensor_update(distL, distF1, distF2, distR, distUF); 
          if     ( ((distF1 <= 1160) || (distF2 <= 1160)) && distUF >= 870 && distL <= 1160 ){decision = 3; break;} // obstacle avoid case for left wall
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distUF >= 870 && distR <= 1160 ){decision = 4; break;} // obstacle avoid  for right wall
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distUF >= 870 )                 {decision = 4; break;} // if obstacle is in the middle 
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distL <=  1160 )        	     {decision = 2; break;} // corner turn case for left corner
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distR <=  1160 )                {decision = 1; break;} //corner turn right corner
          else if( prevDecision == 1 ) 						                                 {decision = 2; break;}
          else /*( prevDecision == 2 )*/					                                 {decision = 1; break;}
		  
      case 6: // up/down motion from left corner
		  delayCount = 0;
		  sensor_update(distL, distF1, distF2, distR, distUF); 
		  while( ((distF1 >= 754)&&(distF2 >= 754)) && (delayCount <= 300)) { // if no wall detected, proceed to move forward for a delay of 500ms
			  forward(); //_delay_ms(20); 
			  delayCount += 150; 
			  sensor_update(distL, distF1, distF2, distR, distUF); 
		  }
				brake();_delay_ms(50);
				turnRight(); _delay_ms(delay); 
				brake();_delay_ms(50);
          decision = 5;
		  break;
      case 7: // up/down motion from right corner
		  delayCount = 0;
		  sensor_update(distL, distF1, distF2, distR, distUF); 
		  while( ((distF1 >= 754)&&(distF2 >= 754) ) && (delayCount <= 300)) { // if no wall detected, proceed to move forward for a delay of 500ms
			  forward(); //_delay_ms(20); 
			  delayCount += 150; 
			  sensor_update(distL, distF1, distF2, distR, distUF); 
		  }
				brake();_delay_ms(50);
				turnLeft(); _delay_ms(delay); 
				brake();_delay_ms(50); 
          decision = 5;
		  break;
	  //default: brake();
	}
  }
  return 0;
}























