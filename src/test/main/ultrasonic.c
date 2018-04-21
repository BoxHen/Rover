#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ultrasonic.h"

// DETECTS BOTH RISING EDGE AND FALLING EDGE OF INT0
// ON THE RISING EDGE , WE START THE COUNTER, WE WILL SET THE FLAG TO ZERO. WAITING FOR THE FLALING EDGE
// AFTER THE FALLING EDGE , WE GET THE DISTANCE
ISR(PCINT0_vect){ //Left
	if(flags & (1 << 0)){
		TCNT1 = 0;
	}else{
		distanceL = (TCNT1)/ 58;
	}
	flags &= ~(1 << 0);
}

ISR(PCINT1_vect){ // Front
	if(flags & (1 << 1)){
		TCNT1 = 0;
	}else{
		distanceF = (TCNT1)/ 58;
	}
	flags &= ~(1 << 1);
}

ISR(PCINT2_vect){ //Right
	if(flags & (1 << 2)){
		TCNT1 = 0;
	}else{
		distanceR = (TCNT1)/ 58;
	}
	flags &= ~(1 << 2);
}
/*============================================================================*/
void init_ultrasonic(){
	// set PORT5, PORT4, PORT3, PORT2, PORT1 and PORT0 to outputs
	DDRC = (1 << PC5 | 1 << PC4 | 1 << PC3 | 1 << PC2 | 1 << PC1);
	DDRB = 1 << PB5;
	//set WGM = 4: CTC mode clear on OCR1A
	TCCR1A = 0x00;
	TCCR1B = 0x01;//set clock no pre-scaling
	// ENABLE EXTERNAL INTERRUPTS
	PCMSK0 = 0x40;// turn on TO ENABLE PCINT[7:0] -- for pcint6
	PCMSK1 = 0x01;// USE PCINT8
	PCMSK2 = 0x10;//USE PCINT20
	PCICR =  0x07;// Any change on any enabled PCINT[7:0], PCINT[14:8], PCINT[23:16] pin will cause an interrupt

	ACSR &= ~(1 << 2);
	// enable global interrupt
	sei();

}
/*============================================================================*/
void distanceLeft(){ //use pcint6 PB5
	flags |= (1 << 0);
	//DISABLE external interrupt
	PCMSK0 = 0x00;
	// send 10us pulse to sensors
	PORTC |= (1 << PC5);
	_delay_us(50);
	PORTC &= ~(1 << PC5);
	//ENABLE external interrupt
	PCMSK0 = 0x40; 
	_delay_ms(60);
	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}

void distanceFront(){ // use pcint8 pc1
	flags |= (1 << 1);
	//DISABLE external interrupt
	PCMSK1 = 0x00;
	// send 10us pulse to sensors
	PORTC |= (1 << PC4);
	_delay_us(50);
	PORTC &= ~(1 << PC4);
	//ENABLE external interrupt
	PCMSK1 = 0x01;
	_delay_ms(60);
	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}

void distanceRight(){ // use pcint20 pc2
	flags |= (1 << 2);
	//DISABLE external interrupt
	PCMSK2 = 0x00;
	// send 10us pulse to sensors
	PORTC |= (1 << PC3);
	_delay_us(50);
	PORTC &= ~(1 << PC3);
	//ENABLE external interrupt
	PCMSK2 = 0x10;
	_delay_ms(60);
	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
}
/*============================================================================*/
/*int main(){
  init_ultrasonic();

  while(1) {
		distanceLeft();
		distanceRight();
		distanceFront();

		if (distanceL < 10){
			PORTB |= (1 << PB5);
		}else{
			PORTB &= ~(1 << PB5);
		}
            
		if (distanceF < 10){
			PORTC |= (1 << PC1);
		}else{
			PORTC &= ~(1 << PC1);
		}
		
		if (distanceR < 10){
			PORTC |= (1 << PC2);
		}else{
			PORTC &= ~(1 << PC2);
		}
  }
  return 0;
}*/