/*-------------------------------------------------------- 
 * http://www.instructables.com/id/Arduino-obstacle-avoider-robot-EASY/
 *  http://www.instructables.com/file/FKR7SE5IA57A2I1/
 *  http://www.instructables.com/id/Arduino-and-L293D-Robot-Part-1-/step2/Wiring-the-L293D-Chip/
 *  https://www.youtube.com/watch?v=QqdgFu96KnA
-----------------------------------------------------------*/
#define trigPin 7
#define echoPin 11
  int m1b = 9;
  int m1f =10;
  int m2f = 12;
 int m2b = 13;

void setup(){
 pinMode(m1f, OUTPUT);
  pinMode(m1b, OUTPUT);
  pinMode(m2f, OUTPUT);
  pinMode(m2b, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop(){
   int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 25){
    digitalWrite(m1f, HIGH);
 digitalWrite(m1b, LOW);
  digitalWrite(m2f, HIGH);
 digitalWrite(m2b, LOW);
 delay(100);
  }
  else {

 digitalWrite(m1f, HIGH);
 digitalWrite(m1b, LOW);
  digitalWrite(m2b, HIGH);
 digitalWrite(m2f, LOW);
 delay(800);
}
  
  
}


