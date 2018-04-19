#include "ultrasonic.h"

int main(){
  // set PORT5, PORT2 and PORT1 to outputs
  DDRC = (1 << PC5 | 1 << PC1 | 1 << PC0 | 1 << PC4);
  //set clock no scaling
  //set WGM = 4: CTC mode clear on OCR1A
  TCCR1A = 0x00;
  TCCR1B = 0x01;
  //ENABLE external interrupt
  EIMSK = 0x03;
  // interrupt to be fired
  // DETECING BOTH RISING EDGE AND FALLING EDGE OF INT0 AND INTB
  EICRA = 0x05;
  // setting ACIC to 0
  ACSR &= ~(1 << 2);
  // enable global interrupt
  sei();

  while(1) {
		find_distance();
		find_distance2();

		if (distance < 10){
			PORTC |= (1 << PC0);
		}else{
			PORTC &= ~(1 << PC0);
		}

		if (distance2 < 10){
			PORTC |= (1 << PC1);
		}else{
			PORTC &= ~(1 << PC1);
		}
  }
  return 0;
}
