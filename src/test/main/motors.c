#include "ultrasonic.h"
#include "motors.h"

/*initialize the PORTs dedicated to the motors.
You always have to call this in main to intialize the PORT I/O
*/
void init_motors(){
	//PB1 -> LEFTA  -- AIN
	//PB2 -> LEFTB  -- BIN
	//PB3 -> RIGHTA -- AIN
	//PB4 -> RIGHTB -- BIN
	DDRB = (1 << PB4 | 1 << PB3 | 1 << PB2 | 1 << PB1 | 1 << PB0); //set as outputs
	/*	DDRB = (1 << PB0); // output to other 328 based off COUNT value
	    DDRD = ~(1 << PD7); //set as input for other 328*/
	DDRD = 1 << PD7; // used to communicate with other 328
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
}

void rightmotor_reverse(){
	PORTB &= ~(1 << PB3);// --AIN:0
	PORTB |= (1 << PB4); // --BIN:1
}
/*==========================BRAKE============================*/
void leftmotor_brake(){
	PORTB |= (1 << PB1);//  --AIN:1
	PORTB |= (1 << PB2); // --BIN:1
}

void rightmotor_brake(){
	PORTB |= (1 << PB3);//  --AIN:1
	PORTB |= (1 << PB4); // --BIN:1
}
/*==========================FORWARD============================*/
void leftmotor_foward(){
	PORTB |= (1 << PB1);//   --AIN:1
	PORTB &= ~(1 << PB2); // --BIN:0
}

void rightmotor_foward(){
	PORTB |= (1 << PB3);//   --AIN:1
	PORTB &= ~(1 << PB4); // --BIN:0
}
/*==========================COAST============================*/
void leftmotor_coast(){
	PORTB &= ~(1 << PB1);//  --AIN:0
	PORTB &= ~(1 << PB2); // --BIN:0
}

void rightmotor_coast(){
	PORTB &= ~(1 << PB3);//  --AIN:0
	PORTB &= ~(1 << PB4); // --BIN:0
}
/*======================================================*/
void brake(){
    leftmotor_brake();
    rightmotor_brake();
}

void turnRight(){
	PORTD |= (1 << PD7); // turn on PD7 so other 328 starts the turnCount
	while( (PINB & (1 << PB0)) ){
	leftmotor_foward();
	rightmotor_reverse();
	}
}

void turnLeft(){
	PORTD |= (1 << PD7); // turn on PD7 so other 328 starts the turnCount
	while( (PINB & (1 << PB0)) ){
	rightmotor_foward();
	leftmotor_reverse();
	}
}

void forward(){
	leftmotor_foward();
	rightmotor_foward();
}

void reverse(){
	leftmotor_reverse();
	rightmotor_reverse();
}
