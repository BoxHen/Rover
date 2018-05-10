#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "ultrasonic.h"
#include "motors.h"
//#include "PWM.h"

/*initialize the PORTs dedicated to the motors.
You always have to call this in main to intialize the PORT I/O
*/
void init_motors(){
	//init_PWM();
	//PB1 -> LEFTA  -- AIN -- PWM_leftA(uint8_t value); -- OCR0A
	//PB2 -> LEFTB  -- BIN -- PWM_rightA(uint8_t value);-- OCR0B
	
	//PB3 -> RIGHTA -- AIN -- PWM_leftB(uint8_t value); -- OCR2A
	//PB4 -> RIGHTB -- BIN -- PWM_rightB(uint8_t value);-- OCR2B
	DDRB = (1 << PB4 | 1 << PB3 | 1 << PB2 | 1 << PB1 | 1 << PB0); //set as outputs
	/*	DDRB = (1 << PB0); // output to other 328 based off COUNT value
	    DDRD = ~(1 << PD7); //set as input for other 328*/
	//DDRB = (1 << PB7);// used to communicate with arduino
	//DDRD = (1 << PD5 | 1 << PD6 | 1 << PD7);// used to communicate with arduino
	brake();
}
/*
Ain	|	Bin	|	Function
____|_______|___________
0	|	0	|	coast
0	|	1	|	reverse
1	|	0	|	forward
1	|	1	|	brake      */
/*==========================REVERSE============================*/
void leftmotor_reverse(){
	PORTB &= ~(1 << PB1);// --AIN:0
	PORTB |= (1 << PB2); // --BIN:1
	//PWM_leftA(0xFF - value);
	//PWM_rightA(0xFF);
}

void rightmotor_reverse( ){
	PORTB &= ~(1 << PB3);// --AIN:0
	PORTB |= (1 << PB4); // --BIN:1
	//PWM_leftB(0xFF - value);
	//PWM_rightB(0xFF);
}
/*==========================BRAKE============================*/
void leftmotor_brake(){
	PORTB |= (1 << PB1);//  --AIN:1
	PORTB |= (1 << PB2); // --BIN:1
	//PWM_leftA(0xFF);
	//PWM_rightA(0xFF);
}

void rightmotor_brake(){
	PORTB |= (1 << PB3);//  --AIN:1
	PORTB |= (1 << PB4); // --BIN:1
	//PWM_leftB(0xFF);
	//PWM_rightB(0xFF);
}
/*==========================FORWARD============================*/
void leftmotor_foward( ){
	PORTB |= (1 << PB1);//   --AIN:1
	PORTB &= ~(1 << PB2); // --BIN:0
	//PWM_leftA(0xFF);
	//PWM_rightA(0x0FF - value);
}

void rightmotor_foward( ){
	PORTB |= (1 << PB3);//   --AIN:1
	PORTB &= ~(1 << PB4); // --BIN:0
	//PWM_leftB(0xFF);
	//PWM_rightB(0x0FF - value);
}
/*==========================COAST============================*/
void leftmotor_coast(){
	PORTB &= ~(1 << PB1);//  --AIN:0
	PORTB &= ~(1 << PB2); // --BIN:0
	//PWM_leftA(0x00);
	//PWM_rightA(0x00);
}

void rightmotor_coast(){
	PORTB &= ~(1 << PB3);//  --AIN:0
	PORTB &= ~(1 << PB4); // --BIN:0
	//PWM_leftB(0x00);
	//PWM_rightB(0x00);
}
/*======================================================*/
void brake(){
    leftmotor_brake();
    rightmotor_brake();
}

void turnRight(){
	//PORTB |= (1 << PB7); // turn on PD7 so other 328 starts the turnCount
	//_delay_ms(50);
	//while( (PIND & (1 << PD5)) ){ // if PD5 is on (from arduino), turn
	leftmotor_foward(); _delay_ms(10);
	rightmotor_reverse(); _delay_ms(10);
	//}
}

void turnLeft(){
	//PORTD |= (1 << PD6); // turn on PD7 so other 328 starts the turnCount
	//_delay_ms(50);
	//while( (PIND & (1 << PD7)) ){
	rightmotor_foward(); _delay_ms(10);
	leftmotor_reverse(); _delay_ms(10);
	//}
}

void forward(){
	leftmotor_foward(); 
	rightmotor_foward();
	
}

void reverse(){
	leftmotor_reverse();
	rightmotor_reverse();
}
