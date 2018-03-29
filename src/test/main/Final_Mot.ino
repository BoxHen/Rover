/*-------------------------------------------------------- 
 * http://www.instructables.com/id/Arduino-obstacle-avoider-robot-EASY/
 *  http://www.instructables.com/file/FKR7SE5IA57A2I1/
 *  http://www.instructables.com/id/Arduino-and-L293D-Robot-Part-1-/step2/Wiring-the-L293D-Chip/
 *  https://www.youtube.com/watch?v=QqdgFu96KnA
-----------------------------------------------------------*/
  int m1 = 9;
  int m2 =10;

void setup(){
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
}
void loop(){
  if (RightSensor <= 5){
    digitalWrite(m1f, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2f, HIGH);
    digitalWrite(m2b, LOW);
    delay(100);
  }
  else if(LeftSensor <=5){
    
    }
  else if(FrontSensor <= 5){
    
    }
  else {
    digitalWrite(m1f, HIGH);
    digitalWrite(m1b, LOW);
    digitalWrite(m2b, HIGH);
    digitalWrite(m2f, LOW);
    delay(800);
  }
}


