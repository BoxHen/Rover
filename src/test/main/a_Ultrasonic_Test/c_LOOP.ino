void loop() {
/*==========================================ULTRASONIC SENSOR=================================================*/
  SonarSensor(trigPin1, echoPin1); //trig->pin3  echo->pin2
  RightSensor = distance;
  SonarSensor(trigPin2, echoPin2); //trig->pin4  echo->pin5
  FrontSensor = distance;

  //SonarSensor(trigPin3, echoPin3); //trig->pin5  echo->pin7
  //LeftSensor = distance;

  Serial.print(" R: ");
  Serial.print(RightSensor);
  Serial.print(" F: ");
  Serial.print(FrontSensor);

  //Serial.print(" - ");
  //Serial.println(RightSensor);
  
/*================================================MOTOR=======================================================*/
  if(RightSensor <=20 && FrontSensor <=15){ // turn left
    //digitalWrite(LeftMotorDirection2, LOW);   digitalWrite(RightMotorDirection2, HIGH); // in1
    analogWrite(PWMoutLeft, 0); analogWrite(PWMoutRight, (val / 4)); 
    digitalWrite(LeftMotorDirection, HIGH);  digitalWrite(RightMotorDirection, LOW); // in2    //delay(100); // delay may cause probs --- test it
    Serial.print(" |--1--| ");
    delay(100);
  }
  else if((RightSensor <=20 && FrontSensor >15) || (RightSensor >20  && FrontSensor >15)){ // forward
    //digitalWrite(LeftMotorDirection2, HIGH);  digitalWrite(RightMotorDirection2, HIGH); // in1
    analogWrite(PWMoutLeft, (val / 4)); analogWrite(PWMoutRight, (val / 4)); 
    digitalWrite(LeftMotorDirection, LOW);    digitalWrite(RightMotorDirection, LOW); // in2
    Serial.print("--2--");
    delay(100);
  }
  else if(RightSensor > 20 && FrontSensor <= 15){ // turn right
    //digitalWrite(LeftMotorDirection2, HIGH);  digitalWrite(RightMotorDirection2, LOW); // in1
    analogWrite(PWMoutLeft, (val / 4)); analogWrite(PWMoutRight, 0); 
    digitalWrite(LeftMotorDirection, LOW);    digitalWrite(RightMotorDirection, HIGH); // in2
    Serial.print("--3--");
    delay(100);
  }
  // will need a reverse!!! but this may require three sensors in the case there is a wall in front and to either side 

  /*================================================PWM=======================================================*/
  /*//val = analogRead(analogPin); // Use if we want to speed/slow motor dynamically
                                 // analogRead will get a value from 0-1023
  analogWrite(PWMoutLeft, (val / 4)); analogWrite(PWMoutRight, (val / 4)); 
   /*analogWrite(pin, value)
      pin: the pin to write to. Allowed data types: int.
      value: the duty cycle: between 0 (always off) and 255 (always on). Allowed data types: int

      analogRead values go from 0 to 1023,
      analogWrite values from 0 to 255

      reference: https://www.tutorialspoint.com/arduino/arduino_pulse_width_modulation.htm */
      
 /*===============================================ENCODER======================================================*/
    n = digitalRead(EncoderPinA);
    if((EncoderPinALast == LOW) && (n == HIGH)) {
      if(digitalRead(EncoderPinB) == LOW) {
        EncoderPosition--;
      } else{
        EncoderPosition++;
      }
      Serial.print (EncoderPosition);
      Serial.print ("/");
    }
    EncoderPinALast = n; 

}
