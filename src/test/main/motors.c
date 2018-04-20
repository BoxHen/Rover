#include "motor.h"

/*initialize the PORTs dedicated to the motors.
You always have to call this in main to intialize the PORT I/O
*/
void init_motors (){

}

void leftmotor_reverse(){

}


void rightmotor_reverse(){

}

void leftmotor_brake(){

}

void rightmotor_brake(){

}


void leftmotor_foward(){

}

void rightmotor_foward(){

}

void leftmotor_coast(){

}

void rightmotor_coast(){

}

void brake(){
    leftmotor_brake();
    rightmotor_brake();
}
