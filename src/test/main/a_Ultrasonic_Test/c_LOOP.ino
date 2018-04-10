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
  if(RightSensor <=7 && FrontSensor <=5){ // turn left
    //digitalWrite(mLeft, LOW); // try to reverse this !!!
    //digitalWrite(mRight, HIGH);
    digitalWrite(LeftMotorDirection, HIGH); digitalWrite(RightMotorDirection, LOW); //reverse->1, Forward->0
    //delay(100); // delay may cause probs --- test it
  }
  else if((RightSensor <=7 && FrontSensor >5) || (RightSensor >7 && FrontSensor >5)){ // forward
    //digitalWrite(mLeft, HIGH); 
    //digitalWrite(mRight, HIGH);
    digitalWrite(LeftMotorDirection, LOW); digitalWrite(RightMotorDirection, LOW); //reverse->1, Forward->0
    //delay(100);
  }
  else if(RightSensor > 7 && FrontSensor <= 5){ // turn right
    //digitalWrite(mLeft, HIGH);
    //digitalWrite(mRight, LOW);
    digitalWrite(LeftMotorDirection, LOW); digitalWrite(RightMotorDirection, HIGH); //reverse->1, Forward->0
    //delay(100);
  }
  // will need a reverse!!! but this may require three sensors in the case there is a wall in front and to either side 

  /*================================================PWM=======================================================*/
  //val = analogRead(analogPin); // Use if we want to speed/slow motor dynamically
                                 // analogRead will get a value from 0-1023
  analogWrite(PWMoutLeft, (val / 4)); // value can be set to constant for specific speed or connected to some input to control motor speed
  analogWrite(PWMoutRight, (val / 4)); 
   /*analogWrite(pin, value)
      pin: the pin to write to. Allowed data types: int.
      value: the duty cycle: between 0 (always off) and 255 (always on). Allowed data types: int

      analogRead values go from 0 to 1023,
      analogWrite values from 0 to 255

      reference: https://www.tutorialspoint.com/arduino/arduino_pulse_width_modulation.htm */
      
 /*===============================================ENCODER======================================================*/
    n = digitalRead(encoder0PinA);
    if ((encoder0PinALast == LOW) && (n == HIGH)) {
      if (digitalRead(encoder0PinB) == LOW) {
        encoder0Pos--;
      } else {
        encoder0Pos++;
      }
      Serial.print (encoder0Pos);
      Serial.print ("/");
    }
    encoder0PinALast = n; 

}
