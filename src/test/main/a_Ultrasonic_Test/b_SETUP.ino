void setup(){
/*==========================================ULTRASONIC SENSOR=================================================*/
  Serial.begin (115200); // was 9600
  pinMode(trigPin1, OUTPUT); pinMode(echoPin1, INPUT);// sets the trigpin as output, sets the echopin as input and following
  pinMode(trigPin2, OUTPUT); pinMode(echoPin2, INPUT);
  //pinMode(trigPin3, OUTPUT); pinMode(echoPin3, INPUT);
/*================================================MOTOR=======================================================*/
  //pinMode(mLeft, OUTPUT); // these were used for running motors at full speed(test)
  //pinMode(mRight, OUTPUT); // PWM will now do that for us 
  pinMode(LeftMotorDirection, OUTPUT);
  pinMode(RightMotorDirection, OUTPUT);
/*=================================================PWM========================================================*/
  pinMode(PWMoutLeft, OUTPUT); // sets the pin as output
  pinMode(PWMoutRight, OUTPUT);
/*===============================================ENCODER======================================================*/
  pinMode(EncoderPinA, INPUT);
  pinMode(EncoderPinB, INPUT);

}
