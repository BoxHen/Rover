/*===============================DEFINITIONS==================================*/
#define trigPin1 3
#define echoPin1 2
#define trigPin2 4
#define echoPin2 5
#define trigPin3 7
#define echoPin3 8
/*============================================================================*/
long duration, distance, RightSensor,FrontSensor,LeftSensor;

void setup(){
Serial.begin (9600);
pinMode(trigPin1, OUTPUT); pinMode(echoPin1, INPUT);// sets the trigpin as output, sets the echopin as input and following
pinMode(trigPin2, OUTPUT); pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT); pinMode(echoPin3, INPUT);
}

void loop() {
SonarSensor(trigPin1, echoPin1); //trig->pin3  echo->pin2
RightSensor = distance;
SonarSensor(trigPin2, echoPin2); //trig->pin4  echo->pin5
LeftSensor = distance;
SonarSensor(trigPin3, echoPin3); //trig->pin5  echo->pin7
FrontSensor = distance;

Serial.print(LeftSensor);
Serial.print(" - ");
Serial.print(FrontSensor);
Serial.print(" - ");
Serial.println(RightSensor);
}
/*================================FUNCTION===================================*/
void SonarSensor(int trigPin,int echoPin){
digitalWrite(trigPin, LOW); // writes low or high to specified pin
/*digitalWrite(pin, value)
    pin: the pin number
    value: HIGH or LOW*/
delayMicroseconds(60); // suggest to use over 60ms measurement cycle, in order
//                        to prevent trigger signal to the echo signal
digitalWrite(trigPin, HIGH);
delayMicroseconds(11); // need at least 10 us to trigger
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH); //NOTICE: The timing of this function has been determined empirically and will probably show errors in longer pulses. Works on pulses from 10 microseconds to 3 minutes in length.
distance = (duration/2) / 29.1;

}
