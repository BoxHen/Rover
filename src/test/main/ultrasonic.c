#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "ultrasonic.h"

uint8_t distanceL = 0x00, distanceF = 0x00, distanceUF = 0x00, distanceR = 0x00;
uint8_t flags = 0x00; // storing zeros until flag is turned on

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
ISR(INT0_vect){
	if(flags & (1 << 3)){
		TCNT1 = 0;
	}else{
		distanceUF = (TCNT1)/ 58;
	}
	flags &= ~(1 << 3); 
}
/*============================================================================*/
void init_ultrasonic(){
	DDRC = (1 << PC5 | 1 << PC4 | 1 << PC3 | 1 << PC2 | 1 << PC1);
	DDRB = (1 << PB7); // LEDS
	DDRD = (1 << PD5 | 1 << PD6 | 1 << PD7); // LEDS
	//set WGM = 4: CTC mode clear on OCR1A
	TCCR1A = 0x00;
	TCCR1B = 0x01;// set clock no pre-scaling
	// ENABLE EXTERNAL INTERRUPTS
	PCMSK0 = 0x40;// use PCINT6
	PCMSK1 = 0x01;// USE PCINT8
	PCMSK2 = 0x10;// USE PCINT20
	PCICR =  0x07;// Any change on any enabled PCINT[7:0], PCINT[14:8], PCINT[23:16] pin will cause an interrupt
	//for INT0
	EIMSK  = 0x01;// turn on INT0
	EICRA  = 0x01;// any logic change on INT0 will generate interrupt request

	sei();	// enable global interrupt

}
/*============================================================================*/
uint8_t distanceLeft(){ //use pcint6 PB7
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
	return distanceL;
}

uint8_t distanceFront(){ // use pcint8 PD5
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
	return distanceF;
}

uint8_t distanceRight(){ // use pcint20 PD6
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
	return distanceR;
}

uint8_t distanceUpperFront(){ // use INT0 PD7
	flags |= (1 << 3);
	//DISABLE external interrupt
	EIMSK = 0x00;
	// send 10us pulse to sensors
	PORTC |= (1 << PC2);
	_delay_us(50);
	PORTC &= ~(1 << PC2);
	//ENABLE external interrupt
	EIMSK = 0x01;
	_delay_ms(60);
	// WAIT FOR INTERRUPTS TO FIRE DURING THE DELAY
	return distanceUF;
}
/*============================================================================*/
