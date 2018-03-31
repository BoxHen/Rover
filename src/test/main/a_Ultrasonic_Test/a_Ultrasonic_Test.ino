// currently using only two sensors!!!

//#include <EEPROM.h>

/*===============================DEFINITIONS FOR ULTRASONIC SENSOR==================================*/
#define trigPin1 3
#define echoPin1 2 // Right

#define trigPin2 4
#define echoPin2 5 // Front

//#define trigPin3 7
//#define echoPin3 8

/*===============================VARIABLES FOR ULTRASONIC SENSOR====================================*/
long duration, distance, RightSensor,FrontSensor,LeftSensor;

/*=====================================VARIABLES FOR MOTOR==========================================*/
int mLeft = 9; //left
int mRight =10; //right
