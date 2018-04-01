void setup(){
/*==========================================ULTRASONIC SENSOR=================================================*/
  Serial.begin (9600);
  pinMode(trigPin1, OUTPUT); pinMode(echoPin1, INPUT);// sets the trigpin as output, sets the echopin as input and following
  pinMode(trigPin2, OUTPUT); pinMode(echoPin2, INPUT);
  //pinMode(trigPin3, OUTPUT); pinMode(echoPin3, INPUT);
/*================================================MOTOR=======================================================*/
  pinMode(mLeft, OUTPUT);
  pinMode(mRight, OUTPUT);
/*=================================================PWM========================================================*/
  pinMode(PWMout, OUTPUT); // sets the pin as output
}
