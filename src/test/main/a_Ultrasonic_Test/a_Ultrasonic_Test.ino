// currently using only two sensors!!!

//#include <EEPROM.h>

/*========================DEFINITIONS/VARIABLES FOR ULTRASONIC SENSOR================================*/
#define trigPin1 3
#define echoPin1 2 // Right

#define trigPin2 4
#define echoPin2 5 // Front

//#define trigPin3 7
//#define echoPin3 8

long duration, distance, RightSensor,FrontSensor,LeftSensor;

/*=====================================VARIABLES FOR MOTOR==========================================*/
int mLeft = 9; //left
int mRight =10; //right
/*================================DEFINITIONS/VARIABLES FOR PWM=====================================*/
// This is the PWMthat goes to motor 
#define PWMout 11 // LED connected to digital pin 9

//int analogPin = 12; // Use this if we decide for variable value - slow down/up motor speed
int val = 400; // variable to store the read value
// this is a little over 1/3 speed where 1023 is max speed


