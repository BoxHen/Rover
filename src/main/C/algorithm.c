#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "algorithm.h"
uint32_t objToEdgeCnt = 0, objToEdgeRead = 0;

void sensor_update(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR, uint8_t distUF){ // read the values from ultrasonic sensor
	distL = distanceLeft();
	distR = distanceRight();
	distF1 = distanceFront1();
	distF2 = distanceFront2();
	distUF = distanceUpperFront();
}
void obstLeftAvoid(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR){ // move forward if you are against the wall of the obstacle
    turnRight(); brake();
	//-------------------------------------------------	
    while(distL <= 20){ 
		objToEdgeCnt++;
		forward();  
		distL = distanceLeft();
	} 
	brake();
	turnLeft();  brake();
	//-------------------------------------------------
	while(distL >= 15){ // after turn we will not be against the wall. move forward until you are
		forward(); distL = distanceLeft();
	} 
	brake();
	//-------------------------------------------------
    while(distL <= 20){ // move forward if you are against the wall of the obstacle
		forward(); 
		distL = distanceLeft();
	} 
	brake();
	//-------------------------------------------------
	turnLeft(); brake();
	//-------------------------------------------------
	distF1 = distanceFront1();
    while( !(distF1 <= 10) || !(distF2 <= 10) || (objToEdgeRead <= objToEdgeCnt) ){ // move forward until front sensor sees a wall
		objToEdgeRead++;
		forward(); 
		distF1 = distanceFront1();
	} 
	objToEdgeRead = 0; objToEdgeCnt = 0; // reset the counts 
	brake();
	//-------------------------------------------------
    turnRight(); brake();
	//-------------------------------------------------
}
void obstRightAvoid(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR){
	turnLeft(); brake();
	//-------------------------------------------------	
	while(distR <= 20){ // move forward if you are against the wall of the obstacle
		objToEdgeCnt++;
		forward();  
		distR = distanceLeft();
	} 
	brake();_delay_ms(50);
	//-------------------------------------------------
    turnRight(); brake();
	//-------------------------------------------------
    while(distR >= 20){ // after turn we will not be aginst the wall. move forward until you are
		forward();  
		distR = distanceRight();
	} 
	brake();
	//-------------------------------------------------
    while(distR <= 20){ // move forward if you are against the wall of the obstacle
		forward(); 
		distR = distanceRight();
	} 
	brake();
	//-------------------------------------------------
    turnRight(); brake();
	
	distF1 = distanceFront1();
    while( ( !(distF1 <= 10) || !(distF2 <= 10) ) || (objToEdgeRead <= objToEdgeCnt) ){ // move forward until front sensor sees a wall
		objToEdgeRead++;
		forward(); 
		distF1 = distanceFront1();
	}
	brake();
	//-------------------------------------------------
    turnLeft(); brake();
	//-------------------------------------------------
}
void reAdjustFrontL(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR, uint8_t distUF){ // f1 is right side of rover 
	sensor_update(distL, distF1, distF2, distR, distUF); 
	if(distF1 <= 20 && distF2 <= 20){
		while(distF1 >= distF2){ // should turn left
			turnRight();
			brake(); 
			sensor_update(distL, distF1, distF2, distR, distUF); 
		}
	}
}
void reAdjustFrontR(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR, uint8_t distUF){ // f1 is right side of rover 
	sensor_update(distL, distF1, distF2, distR, distUF); 
	if(distF1 <= 20 && distF2 <= 20){
		while(distF1 <= distF2){ // should turn right
			turnLeft();  
			brake();  
			sensor_update(distL, distF1, distF2, distR, distUF); 
		}
	}
}































