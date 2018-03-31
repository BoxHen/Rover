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

}
