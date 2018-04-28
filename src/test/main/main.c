#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"
//#include "PWM.h"

int main(){
  //init_PWM();
  init_motors();
  init_ultrasonic();
  
  //uint8_t distanceL = 0x00; uint8_t distanceF = 0x00; uint8_t distanceR = 0x00; uint8_t distanceUF = 0x00; 

  //while(1) {
		turnRight();
		_delay_ms(1050);
		brake();
		
		/*distanceL = distanceLeft();
		distanceR = distanceRight();
		distanceF = distanceFront();
		distanceUF = distanceUpperFront();
		brake();
		if(distanceL < 10){
			PORTB |= (1 << PB7);
			forward();
			_delay_ms(100);
		}
		else{
			PORTB &= ~(1 << PB7);
		}
    //=====================================
		if (distanceF < 10){
			PORTD |= (1 << PD5);
			reverse();
			_delay_ms(100);
		}else{
			PORTD &= ~(1 << PD5);
		}
    //====================================
		if (distanceUF < 10){
			PORTD |= (1 << PD7);
			turnRight();
			_delay_ms(100);
		}else{
			PORTD &= ~(1 << PD7);
		}
	//=====================================
		if (distanceR < 10){
			PORTD |= (1 << PD6);
			turnLeft();
			_delay_ms(100);
		}else{
			PORTD &= ~(1 << PD6);
		}*/
  //}
  return 0;
}
