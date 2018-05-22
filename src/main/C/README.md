==============================================================================
Project Title: CS212 – Lab 10 – infix expression calculator ***v1 allows for exponents***
	Note: files are separated (see included files for summary) and no files are "unnecessary"
=================================================================================
Included files:

	main.c       : This contains the main() - switch cases for rover algorithm 
	
	algorithm.c  : contains some functions for the algrithm of the rover 
	motors.c     : contains functions for motor controls(forward, turn right, left, reverse, coast)
	PWM.c        : contains functions for motor speed control
	ultrasonic.c : contains functions for ultrasonic sensor control(interrupts to read distance)

	algorithm.h  : prototypes for algorithm of rover
	motors.h     : motor function prototypes
	PWM.h        : motor control prototypes
	ultrasonic.h : prototypes for ultrasonic sesnors 

	runRover.txt : terminal commands for running with winAVR
=================================================================================
Running the program: 

	On winAVR - avrdude:
	------------------------------------------
	TO COMPILE: 

	avr-gcc -g -Wall -mmcu=atmega328 -O1 main.c algorithm.c motors.c ultrasonic.c -o main
	avr-objcopy -O ihex -R .eeprom -R .fuse -R .lock main main.hex

	avrdude -c buspirate -P COM5 -p atmega328 -U flash:w:main.hex


	TO RUN:

	used a atmega328 microcontroller chip with the dagu rover 5 setup(additional resources included in resorces folder)

