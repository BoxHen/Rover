#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"
#define delay 1100
uint16_t distL = 0x0000; uint16_t distF1 = 0x0000; uint16_t distF2 = 0x0000; uint16_t distR = 0x0000; uint16_t distUF = 0x0000; 
uint32_t objToEdgeCnt = 0, objToEdgeRead = 0;
void sensor_update(); 
void readjustFrontL();
void readjustFrontR();
void backup();

int main(){
  init_motors();
  init_ultrasonic();
  uint8_t turnCount = 0x00;
  int decision = 1, delayCount = 0, prevDecision = 0;
  
  //uint8_t distL = 0x00; uint8_t distF = 0x00; uint8_t distR = 0x00; uint8_t distUF = 0x00; 

  sensor_update(); _delay_ms(150);
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
				sensor_update();
          while(distL <= 1160 && ( (distF1 >= 754)&&(distF2 >= 754) ) ){ objToEdgeCnt++; forward(); _delay_ms(450); brake(); _delay_ms(10); sensor_update();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
          turnLeft(); _delay_ms(delay); 
				brake();_delay_ms(50);
				sensor_update();
          while(distL >= 1160 && ( (distF1 >= 754)&&(distF2 >= 754) ) ){ forward(); _delay_ms(450); brake(); _delay_ms(10); sensor_update();} // after turn we will not be aginst the wall. move forward until you are
				brake();_delay_ms(50);
				sensor_update();
          while(distL <= 1160 && ( (distF1 >= 754)&&(distF2 >= 754) )){ forward(); _delay_ms(450); brake(); _delay_ms(10);  sensor_update();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
	  if((distF1 <= 754)&&(distF2 <= 754)){turnRight(); _delay_ms(delay);}
          else{turnLeft(); _delay_ms(delay);}
				brake();_delay_ms(50);
		  distF1 = distanceFront1(); distF2 = distanceFront2();
          while( ((distF1 >= 550)&&(distF2 >= 550)) || (objToEdgeRead <= objToEdgeCnt) ){ objToEdgeRead++; forward(); _delay_ms(100); brake(); _delay_ms(10); distF1 = distanceFront1(); distF2 = distanceFront2();} // move forward until front sensor sees a wall
				brake();_delay_ms(50);
				objToEdgeRead = 0; objToEdgeCnt = 0; // reset the counts 
          turnRight(); _delay_ms(delay);
				brake();_delay_ms(50);
          decision = 5;
          break;
      case 4: // obstacle turn right
          turnLeft(); _delay_ms(delay);
				brake();_delay_ms(50);
				sensor_update();
          while(distR <= 1160 && ((distF1 >= 754)&&(distF2 >= 754))){ objToEdgeCnt++; forward(); _delay_ms(450); brake(); _delay_ms(10); sensor_update();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
          turnRight(); _delay_ms(delay);
				brake();_delay_ms(50);
				sensor_update();
          while(distR >= 1160 && ((distF1 >= 754)&&(distF2 >= 754))){ forward(); _delay_ms(450); brake(); _delay_ms(10); sensor_update();} // after turn we will not be aginst the wall. move forward until you are
				brake();_delay_ms(50);
				sensor_update();
          while(distR <= 1160 && ((distF1 >= 754)&&(distF2 >= 754))){ forward(); _delay_ms(450); brake(); _delay_ms(10); sensor_update();} // move forward if you are against the wall of the obstacle
				brake();_delay_ms(50);
	  if((distF1 <= 754)&&(distF2 <= 754)){turnLeft(); _delay_ms(delay);}
          else{turnRight(); _delay_ms(delay);}
				brake();_delay_ms(50);
		  distF1 = distanceFront1(); distF2 = distanceFront2();
          while( ((distF1 >= 550)&&(distF2 >= 550)) || (objToEdgeRead <= objToEdgeCnt) ){ objToEdgeRead++; forward(); _delay_ms(100); brake(); _delay_ms(10); distF1 = distanceFront1(); distF2 = distanceFront2();} // move forward until front sensor sees a wall
				brake();_delay_ms(50);
				objToEdgeRead = 0; objToEdgeCnt = 0; // reset the counts 
				turnLeft(); _delay_ms(delay);
				brake();_delay_ms(50);
          decision = 5;
          break;
      case 5: // move forward until we see a obstacle or wall
		  sensor_update();
          while( (distF1 >= 754)&&(distF2 >= 754) ){ 
            forward(); //_delay_ms(150); brake(); _delay_ms(10); // used so motors move or else it loops to fast for motors to process
	    distF1 = distanceFront1(); distF2 = distanceFront2();
          }
                brake();_delay_ms(50);
				
          readjustFrontL();
	  readjustFrontR();
	  backup();
		 brake();_delay_ms(50);
          sensor_update();
          if     ( ((distF1 <= 1160) || (distF2 <= 1160)) && distUF >= 870 && distL <= 1160 ){decision = 3; break;} // obstacle avoid case for left wall
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distUF >= 870 && distR <= 1160 ){decision = 4; break;} // obstacle avoid  for right wall
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distUF >= 870 )                 {decision = 4; break;} // if obstacle is in the middle !!! this needs fixing since it will try to find a wall !!!
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distL <=  1160 )        	     {decision = 2; break;} // corner turn case for left corner
          else if( ((distF1 <= 1160) || (distF2 <= 1160)) && distR <=  1160 )                {decision = 1; break;} //corner turn right corner// fix this breaks down in the cneter of the mze !!!!!
          else if( prevDecision == 1 ) 						             {decision = 2; break;}
          else /*( prevDecision == 2 )*/					             {decision = 1; break;}
		  
      case 6: // up/dowm motion from left corner
		  delayCount = 0;
		  sensor_update();
		  while( ((distF1 >= 754)&&(distF2 >= 754)) && (delayCount <= 300)) { // if no wall detected, proceed to move forward for a delay of 500ms
			  forward(); //_delay_ms(20); 
			  delayCount += 150; 
			  sensor_update();
		  }
				brake();_delay_ms(50);
				turnRight(); _delay_ms(delay); 
				brake();_delay_ms(50);
          decision = 5;
		  break;
      case 7: // up/down motion from right corner
		  delayCount = 0;
		  sensor_update();
		  while( ((distF1 >= 754)&&(distF2 >= 754) ) && (delayCount <= 300)) { // if no wall detected, proceed to move forward for a delay of 500ms
			  forward(); //_delay_ms(20); 
			  delayCount += 150; 
			  sensor_update();
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
void sensor_update(){ // read the values from ultrasonic sensor
	distL = distanceLeft();
	distR = distanceRight();
	distF1 = distanceFront1();
	distF2 = distanceFront2();
	distUF = distanceUpperFront();
}
void readjustFrontL(){
	sensor_update();
	if(distF1 <= 1160 && distF2 <= 1160){
		while(distF1 >= distF2){ // should turn left
			turnLeft(); _delay_ms(10); 
			brake();     _delay_ms(10);
			sensor_update();
		}
	}
}
void readjustFrontR(){
	sensor_update();
	if(distF1 <= 1160 && distF2 <= 1160){
		while(distF1 <= distF2){ // should turn right
			turnRight(); _delay_ms(10); 
			brake();     _delay_ms(10);
			sensor_update();
		}
	}
}
void backup(){
	if(distF1 <= 174 && distF2 <= 174){ // less than 3cm
		reverse(); _delay_ms(250);
		brake(); _delay_ms(10);	
	}
		
}






















