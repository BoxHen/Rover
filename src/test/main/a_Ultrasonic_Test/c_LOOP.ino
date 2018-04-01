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
    digitalWrite(mLeft, LOW); // try to reverse this !!!
    digitalWrite(mRight, HIGH);
    delay(100);
  }
  else if(RightSensor <=7 && FrontSensor >5){ // forward
    digitalWrite(mLeft, HIGH); 
    digitalWrite(mRight, HIGH);
    delay(100);
  }
  else if(RightSensor > 7 && FrontSensor <= 5){ // turn right
    digitalWrite(mLeft, HIGH);
    digitalWrite(mRight, LOW);
    delay(100);
  }
  // will need a reverse!!!

  /*================================================PWM=======================================================*/
  //val = analogRead(analogPin); // Use if we want to speed/slow motor dynamically
                                 // analogRead will get a value from 0-1023
  analogWrite(ledPin, (val / 4)); // value can be set to constant for specific speed or connected to some input to control motor speed
   /*
      analogWrite(pin, value)
      pin: the pin to write to. Allowed data types: int.
      value: the duty cycle: between 0 (always off) and 255 (always on). Allowed data types: int

      analogRead values go from 0 to 1023,
      analogWrite values from 0 to 255

      reference: https://www.tutorialspoint.com/arduino/arduino_pulse_width_modulation.htm */

}
