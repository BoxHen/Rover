#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ultrasonic.h"

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT0
// ON THE RISING EDGE , WE START THE COUNTER, WE WILL SET THE FLAG TO ZERO. WAITING FOR THE FLALING EDGE
// AFTER THE FALLING EDGE , WE GET THE DISTANCE
ISR(PCINT0_vect){
	if(flags & (1 << 0)){
		TCNT1 = 0;
	}else{
		distance2 = (TCNT1)/ 58;
	}
	flags &= ~(1 << 0);
}

ISR(PCINT1_vect){
	if(flags & (1 << 1)){
		TCNT1 = 0;
	}else{
		distance = (TCNT1)/ 58;
	}
	flags &= ~(1 << 1);
}

ISR(PCINT2_vect){
	if(flags & (1 << 2)){
		TCNT1 = 0;
	}else{
		distance2 = (TCNT1)/ 58;
	}
	flags &= ~(1 << 2);
}
/*============================================================================*/
void init_ultrasonic(){
	// set PORT5, PORT4, PORT3, PORT1 and PORT0 to outputs
  DDRC = (1 << PC5 | 1 << PC4 | 1 << PC3 | 1 << PC1 | 1 << PC0);
  //set clock no scaling
  //set WGM = 4: CTC mode clear on OCR1A
  TCCR1A = 0x00;
  TCCR1B = 0x01;
}
/*============================================================================*/
void distanceLeft(){
	flags |= (1 << 0);
	//DISABLE external interrupt
	PCMSK0 = 0x00;
	// send 10us pulse to sensors
	PORTC |= (1 << PC5);
	_delay_us(50);
	PORTC &= ~(1 << PC5);
	//ENABLE external interrupt
	PCMSK0 = 0x03;
	_delay_ms(60);
	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}

void distanceFront(){
	flags |= (1 << 1);
	//DISABLE external interrupt
	PCMSK1 = 0x00;
	// send 10us pulse to sensors
	PORTC |= (1 << PC4);
	_delay_us(50);
	PORTC &= ~(1 << PC4);
	//ENABLE external interrupt
	PCMSK1 = 0x03;
	_delay_ms(60);
	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}

void distanceRight(){
	flags |= (1 << 2);
	//DISABLE external interrupt
	PCMSK2 = 0x00;
	// send 10us pulse to sensors
	PORTC |= (1 << PC3);
	_delay_us(50);
	PORTC &= ~(1 << PC3);
	//ENABLE external interrupt
	PCMSK2 = 0x03;
	_delay_ms(60);
	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}
/*============================================================================*/
int main(){
  // set PORT5, PORT2 and PORT1 to outputs
  DDRC = (1 << PC5 | 1 << PC4 | 1 << PC3 | 1 << PC1 | 1 << PC0);
  //set clock no scaling
  //set WGM = 4: CTC mode clear on OCR1A
  TCCR1A = 0x00;
  TCCR1B = 0x01;
  //ENABLE external interrupt
  EIMSK = 0x03;
  // interrupt to be fired
  // DETECING BOTH RISING EDGE AND FALLING EDGE OF INT0 AND INTB
  EICRA = 0x05;
  // setting ACIC to 0
  ACSR &= ~(1 << 2);
  // enable global interrupt
  sei();

  while(1) {
		find_distance();
		find_distance2();

		if (distance < 10){
			PORTC |= (1 << PC0);
		}else{
			PORTC &= ~(1 << PC0);
		}

		if (distance2 < 10){
			PORTC |= (1 << PC1);
		}else{
			PORTC &= ~(1 << PC1);
		}
  }
  return 0;
}
