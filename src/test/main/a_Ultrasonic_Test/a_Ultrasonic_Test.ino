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

/*=====================================DEFINITIONS/VARIABLES FOR MOTOR==========================================*/
#define LeftMotorDirection 6 //reverse->1, Forward->0
#define RightMotorDirection 7 
/*================================DEFINITIONS/VARIABLES FOR PWM=====================================*/
// This is the PWMthat goes to motor 
#define PWMoutLeft 10 
#define PWMoutRight 11 

//int analogPin = 13; // Use this if we decide for variable value - slow down/up motor speed
int val = 400; // variable to store the read value
// this is a little over 1/3 speed where 1023 is max speed

/*================================DEFINITIONS/VARIABLES FOR ENCODER=====================================*/
#define EncoderPin = 2; // look up other pins for this later !!!!!!!!!!!!
volatile long pulses; // volatile used since we have ISR reference: https://www.geeksforgeeks.org/understanding-volatile-qualifier-in-c/



