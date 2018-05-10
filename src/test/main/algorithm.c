#include "algorithm.h"

void sensor_update(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR, uint8_t distUF){ // read the values from ultrasonic sensor
	distL = distanceLeft();
	distR = distanceRight();
	distF1 = distanceFront1();
	distF2 = distanceFront2();
	distUF = distanceUpperFront();
}
void obstLeftAvoid(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR){ // move forward if you are against the wall of the obstacle
    turnRight(); _delay_ms(delay); 
		brake();_delay_ms(50);
		
    while(distL <= 20){ 
		objToEdgeCnt++;
		forward(); _delay_ms(100); 
		distL = distanceLeft();
	} 
	brake();_delay_ms(50);
	turnLeft(); _delay_ms(delay); 
	brake();_delay_ms(50);
	
	while(distL >= 15){ // after turn we will not be aginst the wall. move forward until you are
		forward(); _delay_ms(100); distL = distanceLeft();
	} 
	brake();_delay_ms(50);
	
    while(distL <= 20){ // move forward if you are against the wall of the obstacle
		forward(); _delay_ms(100);
		distL = distanceLeft();
	} 
	brake();_delay_ms(50);
	turnLeft(); _delay_ms(delay);
	brake();_delay_ms(50);
	distF1 = distanceFront1();
	
    while( ( !(distF1 <= 10) || !(distF2 <= 10) || (objToEdgeRead <= objToEdgeCnt) ){ // move forward until front sensor sees a wall
		objToEdgeRead++;
		forward(); _delay_ms(100);
		distF1 = distanceFront1();
	} 
	objToEdgeRead = 0; objToEdgeCnt = 0; // reset the counts 
	brake();_delay_ms(50);
    turnRight(); _delay_ms(delay);
	brake();_delay_ms(50);
    decision = 5;
}
void obstRightAvoid(uint8_t distL, uint8_t distF1, uint8_t distF2, uint8_t distR){
	turnLeft(); _delay_ms(delay);
	brake();_delay_ms(50);
		
	while(distR <= 20){ // move forward if you are against the wall of the obstacle
		objToEdgeCnt++;
		forward(); _delay_ms(100); 
		distR = distanceLeft();
	} 
	brake();_delay_ms(50);
    turnRight(); _delay_ms(delay);
	brake();_delay_ms(50);
	
    while(distR >= 20){ // after turn we will not be aginst the wall. move forward until you are
		forward(); _delay_ms(100); 
		distR = distanceRight();
	} 
	brake();_delay_ms(50);
	
    while(distR <= 20){ // move forward if you are against the wall of the obstacle
		forward(); _delay_ms(100);
		distR = distanceRight();
	} 
	brake();_delay_ms(50);
    turnRight(); _delay_ms(delay);
	brake();_delay_ms(50);
	
	distF1 = distanceFront1()
    while( ( !(distF1 <= 10) || !(distF2 <= 10) ) || (objToEdgeRead <= objToEdgeCnt) ){ // move forward until front sensor sees a wall
		objToEdgeRead++;
		forward(); 
		distF1 = distanceFront1();
	}
	brake();_delay_ms(50);
    turnLeft(); _delay_ms(delay);
	brake();_delay_ms(50);
    decision = 5;
}
void reAdjustFront(uint8_t distF1, uint8_t distF2){ // f1 is right side of rover 
	sensor_update();
	if(distF1 <= 20 && distF2 <= 20){
		while(distF1 >= distF2){ // should turn left
			turnRight(); _delay_ms(50); 
			brake();     _delay_ms(10);
			sensor_update();
		}
		while(distF1 <= distF2){ // should turn right
			turnLeft(); _delay_ms(50); 
			brake();     _delay_ms(10);
			sensor_update();
		}
	}
}