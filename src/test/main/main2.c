#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"
//#include "PWM.h"

//uint8_t distF1 = 0x00; uint8_t distF2 = 0x00; //uint8_t distR = 0x00; uint8_t distUF = 0x00;
//uint8_t distL = 0x00;

int main(){
  init_motors();
  init_ultrasonic();
  

  
	/*distL = distanceLeft();
	distR = distanceRight();
	distF1 = distanceFront1();
	distF2 = distanceFront2();
	distUF = distanceUpperFront();
	if(distF1 <= 20 && distF2 <= 20){
		while(distF1 >= distF2){ // should turn left
			turnLeft(); _delay_ms(50); 
			brake();     _delay_ms(10);
			distL = distanceLeft();
			distR = distanceRight();
			distF1 = distanceFront1();
			distF2 = distanceFront2();
			distUF = distanceUpperFront();
		} return 0;
		while(distF1 <= distF2){ // should turn right
			turnRight(); _delay_ms(50); 
			brake();     _delay_ms(10);
			distL = distanceLeft();
			distR = distanceRight();
			distF1 = distanceFront1();
			distF2 = distanceFront2();
			distUF = distanceUpperFront();
		} return 0;
	}
	return 0;
}*/
  //int decision, prevDecision = 0, turnCount = 0;
  
  //uint8_t distanceL = 0x00; uint8_t distanceF = 0x00; uint8_t distanceR = 0x00; uint8_t distanceUF = 0x00; 
uint16_t distanceL = 0x0000;
uint16_t distanceR = 0x0000;
uint16_t distanceF1 = 0x0000;
uint16_t distanceF2 = 0x0000;
uint16_t distanceUF = 0x0000; 
  //if(distanceL < distanceR) {decision = 1;}
  //else {decision = 2;}
  
  while(1) {
		distanceL = distanceLeft();
		distanceR = distanceRight();
		distanceF1 = distanceFront1();
		distanceF2 = distanceFront2();
		distanceUF = distanceUpperFront();
		
		if(distanceL < 580){PORTB |= (1 << PB7);}
		else{PORTB &= ~(1 << PB7);}
    //=====================================
		if (distanceF1 < 580){PORTD |= (1 << PD5);}
		else{PORTD &= ~(1 << PD5);}
    //====================================
		if (distanceUF < 580){PORTD |= (1 << PD7);}
		else{PORTD &= ~(1 << PD7);}
	//=====================================
		if (distanceR < 580){PORTD |= (1 << PD6);}
		else{PORTD &= ~(1 << PD6);}
	//=====================================
		if (distanceF2 < 580){PORTB |= (1 << PB0);}
		else{PORTB &= ~(1 << PB0);}
   
  }
  return 0;
}

  

