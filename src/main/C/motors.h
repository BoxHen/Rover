#ifndef motors_H
#define motors_H

//#define speed 0xAA
void init_motors();

void leftmotor_foward();
void leftmotor_reverse();
void leftmotor_brake();
void leftmotor_coast();

void rightmotor_foward();
void rightmotor_reverse();
void rightmotor_brake();
void rightmotor_coast();

void brake();
void turnRight();
void turnLeft();
void forward();
void reverse();

#endif
