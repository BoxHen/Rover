/*==========================================ULTRASONIC SENSOR=================================================*/
  void SonarSensor(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW); // writes low or high to specified pin
  /*digitalWrite(pin, value)
    pin: the pin number
    value: HIGH or LOW*/
  delayMicroseconds(80); // suggest to use over 60ms measurement cycle, in order
  //                        to prevent trigger signal to the echo signal
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20); // need at least 10 us to trigger
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); //NOTICE: The timing of this function has been determined empirically and will probably show errors in longer pulses. Works on pulses from 10 microseconds to 3 minutes in length.
  distance = (duration/2) / 29.1;
}
