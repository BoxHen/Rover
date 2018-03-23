// David Jiang and Henry Chen
// program to control the movement of the rover
// Using 2 sensors to follow the left edge of the line

#define F_CPU 8000000UL
// defining header files to use on the code
#include <util/delay.h>
#include "motor.h"
#include "qtr_driver.h"
#include <stdint.h>
#include <avr/io.h>


//function prototypes
void move_forward();
void turn_left();
void turn_right();

int main()
{
	//initialize driver and motors
	init_QTR_driver();
	init_motors();

	unsigned char sensor_value; // variable to store the values from the sensor
	
	while(1){ // continuous loop, which checks the values from the sensor and act accordingly
		sensor_value = get_QTR_value();

		if((sensor_value & 0x01) && (sensor_value & 0x02)){ // the values from the sensor is 11, have to turn right
		  turn_right();
		}
		else if((sensor_value == 0x00) || (sensor_value & 0x01)){ // the value from the sensor is 01 or 00, turn left 
		  turn_left();
		}
	    else if (sensor_value & 0x02){ // the value from the sensor is 10, this means the rover is on the track. Move forward
		  move_forward();
		}
		else{
		  move_forward(); // default
		}

	}

	return 0;
}

void move_forward(){ // function for the rover to move forward
  rightmotor_foward();
  leftmotor_foward();
  _delay_ms(125);
  brake();
  _delay_ms(75);
}

void turn_left(){ // function for the rover to turn left
  leftmotor_reverse();
  rightmotor_foward();
  _delay_ms(125);
  brake();
  _delay_ms(75);
}

void turn_right(){ // function for the rover to turn right
  leftmotor_foward();
  rightmotor_reverse();
  _delay_ms(125);
  brake();
  _delay_ms(75);
}
