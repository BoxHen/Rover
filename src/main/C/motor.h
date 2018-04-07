// David Jiang and Henry Chen
/**
* Driver functions for the  Dagu Rover 5
* Created  by I.Sekyonda 2016
*For Atmega32u4 on PapilioDUO
*/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

/*Defining a concatinate function which will make our code more readable
Calling port(DDR,D) would concatinate DDR and the letter D to create DDRD
This makes our code more portable and reader friendly
as we only have to change the letter in the H file and it is changed everywhere else
*/
#define concat(type, letter) type##letter 
#define port(type,letter) concat (type,letter) 


/*Defining the Port Letters and locations for the Leftmortor. Change 
Change these to match your locations*/
#define leftmotorport D
#define leftmotora 3
#define leftmotorb 2
#define leftquadport B
#define leftquada 4
#define leftquadb 5

/*Defining the Port Letters and locations for the Rightmortor
Change these to match your locations*/
#define rightmotorport D
#define rightmotora 7
#define rightmotorb 6
#define rightquadport D
#define rightquada 1
#define rightquadb 4


void init_motors ();

void leftmotor_brake();
void leftmotor_foward();
void leftmotor_reverse();
void leftmotor_coast();

void rightmotor_brake();
void rightmotor_foward();
void rightmotor_reverse();
void rightmotor_coast();

void brake();
uint8_t leftquad_value();
uint8_t rightquad_value();


#endif 